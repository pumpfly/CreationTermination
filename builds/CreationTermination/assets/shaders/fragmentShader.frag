#version 460 core

in vec2 TexCoords;

uniform sampler2D image;
uniform vec4 color;
out vec4 fragColor;

void main() {
    vec4 texColor = color * texture(image, TexCoords);
    if(texColor.a < 0.7) discard;
    fragColor = texColor;
}