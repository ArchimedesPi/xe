#version 330 core

in vec3 fragment_position;
out vec4 color;


void main() {
    color = vec4(abs(fragment_position.z), abs(fragment_position.z), abs(fragment_position.z), 1.0f);
}
