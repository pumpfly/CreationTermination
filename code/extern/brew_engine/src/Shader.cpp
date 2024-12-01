
#include <glad/glad.h>
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

namespace brew {
    struct glStatusData {
        int success;
        const char *shaderName;
        char infoLog[GL_INFO_LOG_LENGTH];
    };

    Shader::Shader(const std::string& vertexShader, const std::string &fragmentShader) {
        auto vertexShaderId = CompileShader(GL_VERTEX_SHADER, vertexShader);
        auto fragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        // Shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShaderId);
        glAttachShader(shaderProgram, fragmentShaderId);
        glLinkProgram(shaderProgram);
        glDetachShader(shaderProgram, vertexShaderId);
        glDetachShader(shaderProgram, fragmentShaderId);

    }

    unsigned int Shader::CompileShader(GLuint shaderType, const std::string& shaderSource){
        auto source = shaderSource.c_str();
        auto shaderID = glCreateShader(shaderType);

        glShaderSource(shaderID, 1, &source, nullptr);
        glCompileShader(shaderID);

        // Error checking/handling
        glStatusData compilationStatus{};
        compilationStatus.shaderName = shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment";
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationStatus.success);
        if(compilationStatus.success == GL_FALSE) {
            glGetShaderInfoLog(shaderID, GL_INFO_LOG_LENGTH, nullptr, compilationStatus.infoLog);
            throw std::runtime_error("ERROR: " + std::string(compilationStatus.shaderName) + " shader compilation failed.\n" +
            std::string(compilationStatus.infoLog));
        }

        return shaderID;
    }

    void Shader::setMatrix(const std::string &uniformName, glm::mat4 matrix) const {
        auto uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));

    }

    void Shader::setVector(const std::string &uniformName, glm::vec4 vector) const {
        auto uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
        glUniform4fv(uniformLocation, 1, glm::value_ptr(vector));

    }

    void Shader::use() const{
        glUseProgram(shaderProgram);
    }

    Shader::~Shader() {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
}