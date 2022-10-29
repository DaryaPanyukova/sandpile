#ifndef LABWORK_3_DARYAPANYUKOVA_SANDPILE_H
#define LABWORK_3_DARYAPANYUKOVA_SANDPILE_H

#include <cstring>
#include <cstdint>

#include <string>

#include "Color.h"
#include "Image.h"



struct ExtendFlags {
    bool up, down, left, right;
    ExtendFlags() {
        up = down = left = right = false;
    }

    bool Any() {
        return up || down || left || right;
    }

    void Reset() {
        up = down = left = right = false;
    }
};

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

    void Save(const std::string& path);

private:

    size_t width_; // width of grid
    size_t height_; // height of grid

    size_t grid_x_; // x-coord of grid left up point (!= 0 because of 'capacity'
    size_t grid_y_; // y-coord
    size_t capacity_width_; // actual width of reserved memory
    size_t capacity_height_;  // actual height of reserved memory

    Image image_;
    uint64_t** grid_;
    uint64_t** tmp_grid_;
    bool isStable_;

    //bool extend_left_, extend_right_, extend_up_, extend_down_;
    ExtendFlags flags_;

    void
    UpdateExtendFlags(size_t x, size_t y);

    void SetWidth(size_t width);

    void SetHeight(size_t height);

    void UpdateImage();
};


#endif //LABWORK_3_DARYAPANYUKOVA_SANDPILE_H
