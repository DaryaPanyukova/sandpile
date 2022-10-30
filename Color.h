#ifndef LABWORK_3_DARYAPANYUKOVA_COLOR_H
#define LABWORK_3_DARYAPANYUKOVA_COLOR_H

#include <cstdint>

struct Color {
public:
    uint8_t r, g, b;
 /*   const Color Sandpile::kWhite = Color(255, 255, 255);
    const Color Sandpile::kGreen = Color(61, 254, 142);
    const Color Sandpile::kPurple = Color(230, 61, 254);
    const Color Sandpile::kYellow = Color(247, 254, 61);
    const Color Sandpile::kBlack = Color(0, 0, 0);*/

    Color() : r(0), g(0), b(0) {}

    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};

static const Color kWhite = Color(255, 255, 255);
static const Color kGreen = Color(61, 254, 142);
static const Color kPurple = Color(230, 61, 254);
static const Color kYellow = Color(247, 254, 61);
static const Color kBlack = Color(0, 0, 0);


#endif //LABWORK_3_DARYAPANYUKOVA_COLOR_H
