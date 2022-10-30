#include <iostream>
#include "Sandpile.h"
/*
const Color Sandpile::kWhite = Color(255, 255, 255);
const Color Sandpile::kGreen = Color(61, 254, 142);
const Color Sandpile::kPurple = Color(230, 61, 254);
const Color Sandpile::kYellow = Color(247, 254, 61);
const Color Sandpile::kBlack = Color(0, 0, 0);*/

void Print(uint64_t** ptr, size_t height, size_t width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << ptr[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void Sandpile::SetWidth(size_t width) {
    width_ = width;
}

void Sandpile::SetHeight(size_t height) {
    height_ = height;
}

void Extend(uint64_t**& array, size_t height, size_t width, ExtendFlags flags) {
    size_t shift_x = width * flags.left;
    size_t shift_y = height * flags.up;

    size_t new_height = height * (flags.up + flags.down + 1);
    size_t new_width = width * (flags.left + flags.right + 1);

    uint64_t** tmp = new uint64_t* [new_height];
    for (size_t i = 0; i < new_height; ++i) {
        tmp[i] = new uint64_t[new_width];
        for (size_t j = 0; j < new_width; ++j) {
            tmp[i][j] = 0;
        }
    }

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            tmp[i + shift_y][j + shift_x] = array[i][j];
        }
    }

    for (size_t i = 0; i < height; ++i) {
        delete[] array[i];
    }
    delete[] array;
    array = tmp;
}

bool Sandpile::DoIteration() {
    isStable_ = true;
    // Print(grid_, capacity_height_, capacity_width_);

    for (size_t y = grid_y_ + 1; y < grid_y_ + height_ - 1; ++y) {
        for (size_t x = grid_x_ + 1; x < grid_x_ + width_ - 1; ++x) {
            if (grid_[y][x] >= 4) {
                isStable_ = false;

                tmp_grid_[y + 1][x]++;
                tmp_grid_[y - 1][x]++;
                tmp_grid_[y][x + 1]++;
                tmp_grid_[y][x - 1]++;
                tmp_grid_[y][x] -= 4;
            }
        }
    }

    size_t tmp_x = grid_x_;
    size_t tmp_y = grid_y_;
    size_t tmp_height = height_;
    size_t tmp_width = width_;
    for (size_t i = tmp_y; i < tmp_y + tmp_height; ++i) {
        for (size_t j = tmp_x; j < tmp_x + tmp_width; ++j) {
            grid_[i][j] = tmp_grid_[i][j];
            if (grid_[i][j] != 0) {
                UpdateExtendFlags(j, i);
            }
        }
    }

    if (flags_.Any()) {
        Extend(tmp_grid_, capacity_height_, capacity_width_, flags_);
        Extend(grid_, capacity_height_, capacity_width_, flags_);

        grid_x_ += capacity_width_ * flags_.left;
        grid_y_ += capacity_height_ * flags_.up;

        capacity_height_ = capacity_height_ * (flags_.up + flags_.down + 1);
        capacity_width_ = capacity_width_ * (flags_.left + flags_.right + 1);
        flags_.Reset();
    }

    //  Print(grid_, capacity_height_, capacity_width_);
    //  std::cout << "\n\n\n";
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
            if (grid_[y + grid_y_][x + grid_x_] == 0) {
                image_.SetColor(x, y, kWhite);
            } else if (grid_[y + grid_y_][x + grid_x_] == 1) {
                image_.SetColor(x, y, kGreen);
            } else if (grid_[y + grid_y_][x + grid_x_] == 2) {
                image_.SetColor(x, y, kPurple);
            } else if (grid_[y + grid_y_][x + grid_x_] == 3) {
                image_.SetColor(x, y, kYellow);
            } else {
                image_.SetColor(x, y, kBlack);
            }
        }
    }
}


Sandpile::Sandpile(size_t width, size_t height, uint64_t** grid) : width_(
        width), height_(height), grid_(grid), image_() {
    flags_ = ExtendFlags();
    capacity_height_ = height_;
    capacity_width_ = width_;
    grid_x_ = 0;
    grid_y_ = 0;
    tmp_grid_ = new uint64_t* [height];
    for (size_t i = 0; i < height; ++i) {
        tmp_grid_[i] = new uint64_t[width];
        for (size_t j = 0; j < width; ++j) {
            tmp_grid_[i][j] = grid[i][j];
        }
    }
}

void Sandpile::UpdateExtendFlags(size_t x, size_t y) {
    flags_.left = flags_.left || (x == 0);
    flags_.right = flags_.right || (x == capacity_width_ - 1);
    flags_.up = flags_.up || (y == 0);
    flags_.down = flags_.down || (y == capacity_height_ - 1);


    grid_x_ -= (x == grid_x_ && grid_x_ != 0);
    grid_y_ -= (y == grid_y_ && grid_y_ != 0);

    width_ += (x == (grid_x_ + width_ - 1));
    height_ += (y == (grid_y_ + height_ - 1));

}




