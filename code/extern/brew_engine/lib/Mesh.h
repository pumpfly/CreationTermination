
#pragma once
#include <vector>


namespace brew {
    class Mesh {
    public:
        explicit Mesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices);
        void draw() const;
        virtual ~Mesh();

        // Delete copy constructor
        Mesh(const Mesh &other) = delete;

        // Explicit move constructor
        Mesh(Mesh &&other) noexcept {
            std::swap(this->VBO, other.VBO);
            std::swap(this->EBO, other.EBO);
            std::swap(this->numIndices , other.numIndices);
        }

        Mesh &operator=(Mesh &&other) noexcept {
            std::swap(this->VBO, other.VBO);
            std::swap(this->EBO, other.EBO);
            std::swap(this->numIndices , other.numIndices);
            return *this;
        }

    private:
        unsigned int VBO = 0;
        unsigned int EBO = 0;
        unsigned int numIndices = 0;
    };
}
