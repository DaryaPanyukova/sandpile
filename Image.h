#ifndef LABWORK_3_DARYAPANYUKOVA_IMAGE_H
#define LABWORK_3_DARYAPANYUKOVA_IMAGE_H

#include <cstdint>

#include <fstream>

#include "Color.h"


class Image {
public:
    Image();

    ~Image() {
        delete[] colors_;
    }

    void SetWidth(size_t width);

    void SetHeight(size_t height);

    Color GetColor(size_t x, size_t y) const;

    void SetColor(size_t x, size_t y, const Color& color);

    void CreateNewImage(size_t width, size_t height);

    void FillFileHeader(char file_header[]) const;

    void FillFileInfoHeader(char informationHeader[]) const;

    void SaveImage(std::string& path);

private:
    const int8_t kHeaderSize = 14;
    const int8_t kInfoHeaderSize = 40;

    size_t width_;
    size_t height_;
    Color* colors_;
};


#endif //LABWORK_3_DARYAPANYUKOVA_IMAGE_H
