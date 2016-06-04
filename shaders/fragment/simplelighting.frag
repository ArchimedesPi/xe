#version 330 core

in vec3 normal;
in vec3 fragment_position;

out vec4 color;

uniform vec4 object_color;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 view_position;

void main() {
    vec3 norm = normalize(normal);
    vec3 light_direction = normalize(light_position - fragment_position);
    vec3 view_direction = normalize(view_position - fragment_position);
    vec3 reflect_direction = reflect(light_direction, norm);

    float specular_strength = 1.0f;

    vec3 ambient = light_color * 0.1;
    vec3 diffuse = max(dot(norm, light_direction), 0.0f) * light_color;

    color = vec4((ambient + diffuse) * object_color.xyz, object_color.z);
}

