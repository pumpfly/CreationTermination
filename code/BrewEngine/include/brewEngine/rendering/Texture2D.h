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

namespace gl3::brewEngine::rendering {
    class Texture2D
    {
        /// @class Texture2D stores image files and loads them
    public:
        Texture2D();
        /// holds the ID of the texture object, used for all texture operations to reference to this particular texture
        unsigned int ID{};

        /// @function FromBytes() generates a Texture2D from the given bytes in GL_RGBA format.
        static Texture2D FromBytes(unsigned int width, unsigned int height, unsigned char* data);

        /// @fucntion FromFile() loads an image file, and generates a Texture2D from it.
        /// image files should be stored inside a folder called "assets" outside the game folder, then the input doesn't have to be the full path
        /// but starting from the path inside the asset folder
        static Texture2D FromFile(const char *filename);

        [[nodiscard]] unsigned int getImageWidth() const { return Width; }
        [[nodiscard]] unsigned int getImageHeight() const { return Height; }

        // binds the texture as the current active GL_TEXTURE_2D texture object
        void Bind() const;

    private:
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
    };

}