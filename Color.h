#ifndef LABWORK_3_DARYAPANYUKOVA_COLOR_H
#define LABWORK_3_DARYAPANYUKOVA_COLOR_H

#include <cstdint>

struct Color {
public:
    uint8_t r, g, b;

    Color() : r(0), g(0), b(0) {}

    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};


#endif //LABWORK_3_DARYAPANYUKOVA_COLOR_H
