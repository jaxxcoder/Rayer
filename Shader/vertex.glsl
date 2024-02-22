#version 330 core
layout (location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(0.4f * aPos.x,0.4f * aPos.y, aPos.z, 1.0);
};