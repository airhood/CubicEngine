#include "Color.h"

using namespace CubicEngine;

const Color Color::Red(1.0f, 0.0f, 0.0f);
const Color Color::Green(0.0f, 1.0f, 0.0f);
const Color Color::Blue(0.0f, 0.0f, 1.0f);
const Color Color::Black(0.0f, 0.0f, 0.0f);
const Color Color::White(1.0f, 1.0f, 1.0f);
const Color Color::Transparent(0.0f, 0.0f, 0.0f, 0.0f);

std::string Color::toString() const {
    return std::string();
}

Color32 Color::toColor32() const {
    return Color32(
        static_cast<unsigned char>(std::clamp(r * 255.0f, 0.0f, 255.0f)),
        static_cast<unsigned char>(std::clamp(g * 255.0f, 0.0f, 255.0f)),
        static_cast<unsigned char>(std::clamp(b * 255.0f, 0.0f, 255.0f)),
        static_cast<unsigned char>(std::clamp(a * 255.0f, 0.0f, 255.0f))
    );
}