#ifndef LABWORK_3_DARYAPANYUKOVA_SANDPILE_H
#define LABWORK_3_DARYAPANYUKOVA_SANDPILE_H

#include <cstring>
#include <cstdint>

#include <string>

#include "Color.h"
#include "Image.h"

class Sandpile {
public:
    static const Color kWhite;
    static const Color kGreen;
    static const Color kPurple;
    static const Color kYellow;
    static const Color kBlack;

    Sandpile(size_t width, size_t height, uint64_t** grid);

    bool DoIteration();

    bool Stable() const;

    void Save(std::string& path);

private:
    size_t width_;
    size_t height_;
    Image image_;
    size_t** grid_;
    bool isStable_;

    bool extend_left_, extend_right_, extend_up_, extend_down_;

    void
    UpdateExtendFlags(size_t x, size_t y, size_t new_width, size_t new_height);

    void SetWidth(size_t width);

    void SetHeight(size_t height);

    void UpdateImage();
};


#endif //LABWORK_3_DARYAPANYUKOVA_SANDPILE_H
