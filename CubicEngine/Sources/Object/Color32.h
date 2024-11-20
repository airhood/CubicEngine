#pragma once

#include <iostream>
#include <algorithm>

namespace CubicEngine {
    class Color32 {
    public:
        char r;
        char g;
        char b;
        char a;

        Color32(char red = 0.0f, char green = 0.0f, char blue = 0.0f, char alpha = 1.0f)
            : r(red), g(green), b(blue), a(alpha) {}

        static const Color32 Red;
        static const Color32 Green;
        static const Color32 Blue;
        static const Color32 Black;
        static const Color32 White;
        static const Color32 Transparent;

        std::string toString() const;

        bool operator==(const Color32& other) const {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

        bool operator!=(const Color32& other) const {
            return !(*this == other);
        }

        Color32 operator+(const Color32& other) const {
            return Color32(
                std::min(r + other.r, 255),
                std::min(g + other.g, 255),
                std::min(b + other.b, 255),
                std::min(a + other.a, 255)
            );
        }

        Color32 operator-(const Color32& other) const {
            return Color32(
                std::max(r - other.r, 0),
                std::max(g - other.g, 0),
                std::max(b - other.b, 0),
                std::max(a - other.a, 0)
            );
        }

        Color32 operator*(const Color32& other) const {
            return Color32(
                std::min(r * other.r, 255),
                std::min(g * other.g, 255),
                std::min(b * other.b, 255),
                std::min(a * other.a, 255)
            );
        }

        Color32 operator/(const Color32& other) const {
            return Color32(
                std::min(r / other.r, 255),
                std::min(g / other.g, 255),
                std::min(b / other.b, 255),
                std::min(a / other.a, 255)
            );
        }

        Color32 operator*(char multiplier) const {
            return Color32(
                std::min(r * multiplier, 255),
                std::min(g * multiplier, 255),
                std::min(b * multiplier, 255),
                std::min(a * multiplier, 255)
            );
        }

        Color32 operator/(char divisor) const {
            if (divisor == 0) {
                std::cerr << "Error: Cannot divide by zero!" << std::endl;
                return *this;
            }
            return Color32(
                std::min(r / divisor, 255),
                std::min(g / divisor, 255),
                std::min(b / divisor, 255),
                std::min(a / divisor, 255)
            );
        }
    };
}
