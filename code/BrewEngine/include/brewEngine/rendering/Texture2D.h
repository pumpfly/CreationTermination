/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#pragma once

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
public:
    Texture2D();
    // holds the ID of the texture object, used for all texture operations to reference to this particular texture
    unsigned int ID{};
    // texture image dimensions
    unsigned int Width, Height; // width and height of loaded image in pixels
    // texture Format
    unsigned int Internal_Format; // format of texture object
    unsigned int Image_Format; // format of loaded image
    // texture configuration
    unsigned int Wrap_S; // wrapping mode on S axis
    unsigned int Wrap_T; // wrapping mode on T axis
    unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels

    // FromBytes generates a Texture2D from the given bytes in GL_RGBA format.
    static Texture2D FromBytes(unsigned int width, unsigned int height, unsigned char* data);

    // FromFile loads an image file, and generates a Texture2D from it.
    static Texture2D FromFile(const char *filename);

    // binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;

private:

};
