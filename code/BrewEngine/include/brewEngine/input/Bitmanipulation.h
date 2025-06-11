#pragma once
#include <cstdint>
#include <iostream>

namespace gl3::brewEngine::input {
    class Bitmanipulation {
    public:
        static void setBit(uint8_t& byte, int bitIndex) {
            byte |= (1 << bitIndex);
        }

        static void clearBit(uint8_t& byte, int bitIndex) {
            byte &= ~(1 << bitIndex);
        }

        static void toggleBit(uint8_t& byte, int bitIndex) {
            byte ^= (1 << bitIndex);
        }

        static bool isBitSet(uint8_t byte, int bitIndex) {
            return byte & (1 << bitIndex);
        }

        static void printBits(uint8_t byte) {
            for (int i = 7; i >= 0; --i) {
                std::cout << ((byte >> i) & 1);
            }
            std::cout << std::endl;
        }
    };
}
