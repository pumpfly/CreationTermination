/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/

#include "brewEngine/rendering/ResourceManager.h"

namespace gl3::brewEngine::rendering {

    // Instantiate static variables
    std::map<std::string, Texture2D> ResourceManager::Textures;
    std::map<std::string, Shader> ResourceManager::Shaders;

    Texture2D ResourceManager::LoadTexture(const char *file, bool alpha, const std::string& name)
    {
        Textures[name] = Texture2D::FromFile(file);
        return Textures[name];
    }

    Texture2D &ResourceManager::GetTexture(const std::string& name)
    {
        return Textures[name];
    }

    void ResourceManager::Clear()
    {
        // (properly) delete all shaders
        //for (auto iter : Shaders)
        //    glDeleteProgram(iter.second.ID);
        // (properly) delete all textures
        for (auto iter : Textures)
            glDeleteTextures(1, &iter.second.ID);
    }

}
