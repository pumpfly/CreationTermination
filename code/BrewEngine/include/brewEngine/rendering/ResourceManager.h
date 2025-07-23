/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/

#pragma once
#include <map>

#include "Shader.h"
#include "Texture2D.h"

namespace gl3::brewEngine::rendering {
    class ResourceManager {

    public:
        // resource storage
        static std::map<std::string, Shader>    Shaders;
        static std::map<std::string, Texture2D> Textures;
        // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
        // loads (and generates) a texture from file
        static Texture2D LoadTexture(const char *file, bool alpha, const std::string& name);
        // retrieves a stored texture
        static Texture2D &GetTexture(const std::string& name);
        // properly de-allocates all loaded resources
        static void      Clear();
    private:
        // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
        ResourceManager() { }
    };

}