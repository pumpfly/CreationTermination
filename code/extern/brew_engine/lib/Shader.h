//
// Created by Lisa B on 22/10/2024.
//

#pragma once

#include <string>
#include <filesystem>
#include "glm/glm.hpp"

namespace brew {
    class Shader {

    public:
        explicit Shader(const std::string& vertexShader, const std::string &fragmentShader);
        virtual ~Shader();

        // Delete copy constructor
        Shader(const Shader &shader) = delete;

        // Explicit move constructor
        Shader(Shader &&other) noexcept {
            std::swap(this->shaderProgram, other.shaderProgram);
            std::swap(this->vertexShader, other.vertexShader);
            std::swap(this->fragmentShader, other.fragmentShader);
        }

        Shader &operator=(Shader &&other) noexcept {
            std::swap(this->shaderProgram, other.shaderProgram);
            std::swap(this->vertexShader, other.vertexShader);
            std::swap(this->fragmentShader, other.fragmentShader);
            return *this;
        }

        void use() const;
        void setMatrix(const std::string &uniformName, glm::mat4 matrix) const;
        void setVector(const std::string &uniformName, glm::vec4 vector) const;


    private:
        unsigned int CompileShader(GLuint shaderType, const std::string& shaderSource);

        unsigned int shaderProgram = 0;
        unsigned int vertexShader = 0;
        unsigned int fragmentShader = 0;

    };
}

const std::string defaultVertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec3 aPos;
    uniform mat4 mvp;
    void main() {
        gl_Position = mvp * vec4(aPos.xyz, 1.0);
    }
)";

const std::string defaultFragmentShaderSource = R"(
    #version 460 core
    uniform vec4 color;
    out vec4 fragColor;
    void main() {
        //fragColor = color;
        fragColor = vec4(1, 0, 0, 1);
    }
)";


