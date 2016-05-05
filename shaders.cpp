#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>

#include "shaders.h"
#include "exceptions.h"

Shader::Shader(std::string code_, GLenum shader_type_) {
    shader_type = shader_type_;

    const GLchar *code = code_.c_str();

    shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &code, NULL);
    glCompileShader(shader_id);

    GLint success; GLchar error_log[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_id, 512, NULL, error_log);
        throw ShaderCompileException(std::string(error_log));
    }
}

Shader::~Shader() {
    glDeleteShader(shader_id);
}

Shader Shader::fromFile(std::string path, GLenum shader_type_) {
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::badbit);
    shader_file.open(path);
    std::stringstream file_stream; file_stream << shader_file.rdbuf();

    return Shader(file_stream.str(), shader_type_);
}

Shader Shader::fromString(std::string code, GLenum shader_type_) {
    return Shader(code, shader_type_);
}


ShaderProgram::ShaderProgram() {
    shader_program_id = glCreateProgram();
}

ShaderProgram &ShaderProgram::addShader(Shader shader) {
    glAttachShader(shader_program_id, shader.shader_id);
    return *this;
}

ShaderProgram &ShaderProgram::link() {
    glLinkProgram(shader_program_id);

    GLint success; GLchar error_log[512];
    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program_id, 512, NULL, error_log);
        throw ShaderLinkException(std::string(error_log));
    }
    
    return *this;
}

void ShaderProgram::use() {
    glUseProgram(shader_program_id);
}

GLuint ShaderProgram::uniform(std::string uniform) {
    return glGetUniformLocation(shader_program_id, uniform.c_str());
}
