#version 330 core
in vec2 texcoord;

out vec4 color;

uniform sampler2D texture_;

void main() {
    color = texture(texture_, texcoord);
}
