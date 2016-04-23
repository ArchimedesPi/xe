#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>

#include "shaders.h"


GLuint load_shader_from_string(const char *shader_string, GLenum shader_type) {
    GLuint shader;
    shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_string, NULL);
    glCompileShader(shader);
    
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "shader (" << shader << ") compilation failed: " << infoLog << '\n';
    }

    return shader;
}

GLuint load_shader_from_file(const char *path, GLenum shader_type) {
    std::ifstream shader_in(path);
    std::string shader_string((std::istreambuf_iterator<char>(shader_in)),
                std::istreambuf_iterator<char>());
    const char* shader_c_string = shader_string.c_str();

    return load_shader_from_string(shader_c_string, shader_type);
}

void link_shader_program(GLuint shader_program) {
    glLinkProgram(shader_program);

    GLint success;
    GLchar info[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info);
        std::cerr << "shader program (" << shader_program << ") compilation failed: " << info << '\n';
    }
}
