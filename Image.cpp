#include "Image.h"


void Image::SetColor(size_t x, size_t y, const Color& color) {
    colors_[y * width_ + x] = color.table_index;
}


void Image::SaveImage(const std::string& path) {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    char bmp_pad[1] = {0};
    uint8_t padding_amount = ((4 - (width_ * kBytesPerPixel) % 4) % 4);

    char file_header[kHeaderSize];
    char info_header[kInfoHeaderSize];
    char color_table[kColorTableSize];

    FillFileHeader(file_header);
    FillFileInfoHeader(info_header);
    FillFileColorTable(color_table);

    f.write(file_header, kHeaderSize);
    f.write(info_header, kInfoHeaderSize);
    f.write(color_table, kColorTableSize);

    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            char tmp = static_cast<char>(GetColor(x, y));
            char color[] = {tmp};
            f.write(color, kBytesPerPixel);
        }
        f.write(bmp_pad, padding_amount);
    }
    f.close();
}

void Image::FillFileHeader(char file_header[]) const {
    for (int32_t i = 0; i < kHeaderSize; ++i) {
        file_header[i] = 0;
    }
    uint8_t padding_amount = ((4 - (width_ * kBytesPerPixel) % 4) % 4);

    int stride = width_ * kBytesPerPixel + padding_amount;
    int file_size = kHeaderSize + kInfoHeaderSize +
                    kColorTableSize + stride * height_;

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

void Image::FillFileColorTable(char color_table[]) const {
    for (int32_t i = 0; i < kColorTableSize; ++i) {
        color_table[i] = 0;
    }
    color_table[0] = kWhite.b;
    color_table[1] = kWhite.g;
    color_table[2] = kWhite.r;

    color_table[4] = kGreen.b;
    color_table[5] = kGreen.g;
    color_table[6] = kGreen.r;


    color_table[8] = kPurple.b;
    color_table[9] = kPurple.g;
    color_table[10] = kPurple.r;


    color_table[12] = kYellow.b;
    color_table[13] = kYellow.g;
    color_table[14] = kYellow.r;


    color_table[16] = kBlack.b;
    color_table[17] = kBlack.g;
    color_table[18] = kBlack.r;
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
    info_header[12] = 1;

    // Bits per pixel (RGB)
    info_header[14] = kBytesPerPixel * 8;

    // Color amount
    info_header[32] = 5;
}

uint8_t Image::GetColor(size_t x, size_t y) const {
    return colors_[y * width_ + x];
}

void Image::SetWidth(size_t width) {
    width_ = width;
}

void Image::SetHeight(size_t height) {
    height_ = height;
}

void Image::CreateNewImage(size_t width, size_t height) {
    if (width != width_ || height != height_) {
        delete[] colors_;
        colors_ = new uint8_t[width * height];
    }
    SetWidth(width);
    SetHeight(height);
}

Image::Image() : width_(0), height_(0), colors_(nullptr) {}

