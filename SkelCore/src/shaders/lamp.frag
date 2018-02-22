#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    FragColor = vec4(1.0);
}