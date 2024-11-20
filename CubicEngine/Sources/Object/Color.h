#pragma once

#include <iostream>
#include <algorithm>

#include "Color32.h"

namespace CubicEngine {
    class Color {
    public:
        float r;
        float g;
        float b;
        float a;

        Color(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f)
            : r(red), g(green), b(blue), a(alpha) {}

        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Black;
        static const Color White;
        static const Color Transparent;

        std::string toString() const;

        bool operator==(const Color& other) const {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

        bool operator!=(const Color& other) const {
            return !(*this == other);
        }

        Color operator+(const Color& other) const {
            return Color(
                std::min(r + other.r, 1.0f),
                std::min(g + other.g, 1.0f),
                std::min(b + other.b, 1.0f),
                std::min(a + other.a, 1.0f)
            );
        }

        Color operator-(const Color& other) const {
            return Color(
                std::max(r - other.r, 0.0f),
                std::max(g - other.g, 0.0f),
                std::max(b - other.b, 0.0f),
                std::max(a - other.a, 0.0f)
            );
        }

        Color operator*(const Color& other) const {
            return Color(
                std::min(r * other.r, 1.0f),
                std::min(g * other.g, 1.0f),
                std::min(b * other.b, 1.0f),
                std::min(a * other.a, 1.0f)
            );
        }

        Color operator/(const Color& other) const {
            return Color(
                std::min(r / other.r, 1.0f),
                std::min(g / other.g, 1.0f),
                std::min(b / other.b, 1.0f),
                std::min(a / other.a, 1.0f)
            );
        }

        Color operator*(float multiplier) const {
            return Color(
                std::min(r * multiplier, 1.0f),
                std::min(g * multiplier, 1.0f),
                std::min(b * multiplier, 1.0f),
                std::min(a * multiplier, 1.0f)
            );
        }
        
        Color operator/(float divisor) const {
            if (divisor == 0) {
                std::cerr << "Error: Cannot divide by zero!" << std::endl;
                return *this;
            }
            return Color(
                std::min(r / divisor, 1.0f),
                std::min(g / divisor, 1.0f),
                std::min(b / divisor, 1.0f),
                std::min(a / divisor, 1.0f)
            );
        }

        Color32 toColor32() const;
    };
}
