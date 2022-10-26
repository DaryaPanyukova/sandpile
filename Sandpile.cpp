#include "Sandpile.h"

const Color Sandpile::kWhite = Color(255, 255, 255);
const Color Sandpile::kGreen = Color(61, 254, 142);
const Color Sandpile::kPurple = Color(230, 61, 254);
const Color Sandpile::kYellow = Color(247, 254, 61);
const Color Sandpile::kBlack = Color(0, 0, 0);

void Sandpile::SetWidth(size_t width) {
    width_ = width;
}

void Sandpile::SetHeight(size_t height) {
    height_ = height;
}

bool Sandpile::DoIteration() {
    size_t new_width = width_ + extend_left_ + extend_right_;
    size_t new_height = height_ + extend_up_ + extend_down_;

    uint64_t** new_grid = new uint64_t* [new_height];

    for (size_t y = 0; y < new_height; ++y) {
        new_grid[y] = new uint64_t[new_width];
        for (size_t x = 0; x < new_width; ++x) {
            new_grid[y][x] = 0;
        }
    }

    for (size_t y = 0; y < height_; ++y) {
          for (size_t x = 0; x < width_; ++x) {
              new_grid[y + extend_up_][x + extend_left_] = grid_[y][x];
          }
    }

    bool prev_ext_up = extend_up_;
    bool prev_ext_left = extend_left_;
    extend_up_ = extend_left_ = extend_down_ = extend_right_ = false;
    isStable_ = true;
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            if (grid_[y][x] >= 4) {
                isStable_ = false;

                new_grid[y + 1 + prev_ext_up][x + prev_ext_left]++;
                new_grid[y - 1 + prev_ext_up][x + prev_ext_left]++;
                new_grid[y + prev_ext_up][x + 1 + prev_ext_left]++;
                new_grid[y + prev_ext_up][x - 1 + prev_ext_left]++;
                new_grid[y + prev_ext_up][x + prev_ext_left] -= 4;

                UpdateExtendFlags(x, y + 1, width_, height_);
                UpdateExtendFlags(x, y - 1, width_, height_);
                UpdateExtendFlags(x + 1, y, width_, height_);
                UpdateExtendFlags(x - 1, y, width_, height_);
            }
        }
    }

    for (size_t i = 0; i < height_; ++i) {
        delete[] grid_[i];
    }
    delete[] grid_;

    SetHeight(new_height);
    SetWidth(new_width);

    grid_ = new_grid;
    return isStable_;
}

bool Sandpile::Stable() const {
    return isStable_;
}

void Sandpile::Save(const std::string& path) {
    UpdateImage();
    image_.SaveImage(path);
}

void Sandpile::UpdateImage() {
    image_.CreateNewImage(width_, height_);
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            if (grid_[y][x] == 0) {
                image_.SetColor(x, y, kWhite);
            } else if (grid_[y][x] == 1) {
                image_.SetColor(x, y, kGreen);
            } else if (grid_[y][x] == 2) {
                image_.SetColor(x, y, kPurple);
            } else if (grid_[y][x] == 3) {
                image_.SetColor(x, y, kYellow);
            } else {
                image_.SetColor(x, y, kBlack);
            }
        }
    }
}


Sandpile::Sandpile(size_t width, size_t height, uint64_t** grid) : width_(
        width), height_(height), grid_(grid), image_(), extend_right_(
        false), extend_left_(false), extend_up_(false), extend_down_(false) {}

void Sandpile::UpdateExtendFlags(size_t x, size_t y,
                                 size_t new_width, size_t new_height) {
    extend_left_ = extend_left_ || (x == 0);
    extend_right_ = extend_right_ || (x == new_width - 1);
    extend_up_ = extend_up_ || (y == 0);
    extend_down_ = extend_down_ || (y == new_height - 1);
}




