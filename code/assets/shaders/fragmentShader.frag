#version 460 core

in vec2 TexCoords;

uniform sampler2D image;
uniform vec4 color;
out vec4 fragColor;

void main() {
    fragColor = color * texture(image, TexCoords);
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}