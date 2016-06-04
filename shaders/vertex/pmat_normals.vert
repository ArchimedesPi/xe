#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal_;

out vec3 normal;
out vec3 fragment_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalmat;


void main() {
    gl_Position = projection * view * model * vec4(position, 1.0f);
    normal = normalmat * normal_;
    fragment_position = vec3(model * vec4(position, 1.0f));
}
