#version 330 core

in vec3 ourColor;
in vec2 texCoord;

out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    //color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    color = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
}
