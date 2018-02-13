#version 330 core

layout(location = 0) in vec3 aPos;

uniform vec4 vertexColor;
uniform mat4 transform;

out vec4 out_vertexColor;

void main()
{
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    out_vertexColor = vertexColor;
}