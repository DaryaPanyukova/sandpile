#include "Image.h"



void Image::SetColor(size_t x, size_t y, const Color& color) {
    colors_[y * width_ + x].r = color.r;
    colors_[y * width_ + x].g = color.g;
    colors_[y * width_ + x].b = color.b;
}


void Image::SaveImage(std::string& path) {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    char bmp_pad[3] = {0, 0, 0};
    uint8_t padding_amount = ((4 - (width_ * 3) % 4) % 4);

    char file_header[kHeaderSize];
    char info_header[kInfoHeaderSize];

    FillFileHeader(file_header);
    FillFileInfoHeader(info_header);


    f.write(file_header, kHeaderSize);
    f.write(info_header, kInfoHeaderSize);

    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            Color tmp = GetColor(x, y);
            char r = static_cast<char>(tmp.r);
            char g = static_cast<char>(tmp.g);
            char b = static_cast<char>(tmp.b);

            char color[] = {b, g, r};
            f.write(color, 3);
        }
        f.write(bmp_pad, padding_amount);
    }
    f.close();
}

void Image::FillFileHeader(char file_header[]) const {
    for (int32_t i = 0; i < kHeaderSize; ++i) {
        file_header[i] = 0;
    }
    uint8_t padding_amount = ((4 - (width_ * 3) % 4) % 4);
    uint8_t file_size = kHeaderSize + kInfoHeaderSize +
                    width_ * height_ * 3 +
                    padding_amount * height_;

    // file type
    file_header[0] = 'B';
    file_header[1] = 'M';

    // file size
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;

    // pixel data offset
    file_header[10] = kHeaderSize + kInfoHeaderSize;
}

void Image::FillFileInfoHeader(char info_header[]) const {
    for (int32_t i = 0; i < kInfoHeaderSize; ++i) {
        info_header[i] = 0;
    }
    // Header size
    info_header[0] = kInfoHeaderSize;

    // Image width
    info_header[4] = width_;
    info_header[5] = width_ >> 8;
    info_header[6] = width_ >> 16;
    info_header[7] = width_ >> 24;

    // Image height
    info_header[8] = height_;
    info_header[9] = height_ >> 8;
    info_header[10] = height_ >> 16;
    info_header[11] = height_ >> 24;


    // Planes
    info_header[12] = width_;
    info_header[13] = width_ >> 8;

    // Bits per pixel (RGB)
    info_header[14] = 24;
}

Color Image::GetColor(size_t x, size_t y) const {
    return colors_[y * width_ + x];
}

void Image::SetWidth(size_t width) {
    width_ = width;
}

void Image::SetHeight(size_t height) {
    height_ = height;
}

void Image::CreateNewImage(size_t width, size_t height) {
    delete[] colors_;
    colors_ = new Color[width * height];
    SetWidth(width);
    SetHeight(height);
}

Image::Image() : width_(0), height_(0), colors_(nullptr) {}

