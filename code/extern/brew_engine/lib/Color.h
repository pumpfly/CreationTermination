#pragma once

#include <cstdint>

namespace brew {
    class Color {
    public:
        Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);
        std::uint8_t r;        // Color red value
        std::uint8_t g;        // Color green value
        std::uint8_t b;        // Color blue value
        std::uint8_t a;        // Color alpha value
    private:
    };
}
