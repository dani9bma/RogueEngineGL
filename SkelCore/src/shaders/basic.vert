#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform vec4 vertexColor;
uniform mat4 transform;

out vec4 out_vertexColor;
out vec2 TexCoord;

void main()
{
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    out_vertexColor = vec4(aColor, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}