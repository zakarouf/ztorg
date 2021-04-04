#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertColors;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertColors = vec4(1.0, 0.1, 0.2, 1.0);
}