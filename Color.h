#ifndef LABWORK_3_DARYAPANYUKOVA_COLOR_H
#define LABWORK_3_DARYAPANYUKOVA_COLOR_H

#include <cstdint>

struct Color {
public:
    uint8_t r, g, b;
    uint8_t table_index;

    Color() : r(0), g(0), b(0) {}

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t index) :
            r(r), g(g), b(b), table_index(index) {}
};

static const Color kWhite = Color(255, 255, 255, 0);
static const Color kGreen = Color(61, 254, 142, 1);
static const Color kPurple = Color(230, 61, 254, 2);
static const Color kYellow = Color(247, 254, 61, 3);
static const Color kBlack = Color(0, 0, 0, 4);


#endif //LABWORK_3_DARYAPANYUKOVA_COLOR_H
