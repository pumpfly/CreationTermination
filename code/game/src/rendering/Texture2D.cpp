/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "glad/glad.h"
#include <GL/gl.h>

#include "Texture2D.h"


#include "Shader.h"
#include "../Assets.h"

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <string>

#include "../stb_image.h"

Texture2D::Texture2D( )
    : Width(0), Height(0), Internal_Format(GL_RGBA), Image_Format(GL_RGBA), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    glGenTextures(1, &this->ID);
}

Texture2D Texture2D::FromBytes(unsigned int width, unsigned int height, unsigned char* data)
{
    Texture2D newTex;
    newTex.Width = width;
    newTex.Height = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, newTex.ID);
    glTexImage2D(GL_TEXTURE_2D, 0, newTex.Internal_Format, width, height, 0, newTex.Image_Format, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, newTex.Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, newTex.Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, newTex.Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, newTex.Filter_Max);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return newTex;
}

Texture2D Texture2D::FromFile(const char* filename) {
    int width, height, nrChannels;
    auto path = gl3::resolveAssetPath(filename).string();

    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    std::cout << "Texture2D.cpp: \n\tImage height = " << height << "\n\tImage width = " << width
    << "\n\tFile from path: " << path << std::endl;

    if(!data) {
        std::cerr << "Failed to load image" << std::endl;
        exit(-1);
    }
    if(nrChannels != 4) {
        std::cerr << "Wrong image format, num channels: " << nrChannels << std::endl;
        exit(-1);
    }

    Texture2D newTex = FromBytes(width, height, data);

    stbi_image_free(data);

    return newTex;
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}