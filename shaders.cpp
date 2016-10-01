#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>

#include <yaml-cpp/yaml.h>

#include "shaders.h"
#include "exceptions.h"

#include "services/locator.h"

using namespace services;


ShaderFile::ShaderFile(std::string code_, GLenum shader_type_) {
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

ShaderFile::~ShaderFile() {
    glDeleteShader(shader_id);
}

ShaderFile ShaderFile::fromFile(std::string path, GLenum shader_type_) {
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::badbit);
    shader_file.open(path);
    std::stringstream file_stream; file_stream << shader_file.rdbuf();

    return ShaderFile(file_stream.str(), shader_type_);
}

ShaderFile ShaderFile::fromString(std::string code, GLenum shader_type_) {
    return ShaderFile(code, shader_type_);
}


Shader::Shader() {
    shader_program_id = glCreateProgram();
}

Shader &Shader::loadFromManifest(std::string resource) {
    auto resLocator = &Locator::resource();

    YAML::Node manifest = YAML::LoadFile(resLocator->pathTo(resource));

    this->display_name = manifest["display_name"].as<std::string>();
    
    this->addShaderFile(ShaderFile::fromFile(
                resLocator->pathTo(manifest["shaders"]["vertex"].as<std::string>()),
                GL_VERTEX_SHADER));
    this->addShaderFile(ShaderFile::fromFile(
                resLocator->pathTo(manifest["shaders"]["fragment"].as<std::string>()),
                GL_FRAGMENT_SHADER));

    return *this;
}

Shader &Shader::addShaderFile(ShaderFile shader) {
    glAttachShader(shader_program_id, shader.shader_id);
    return *this;
}

Shader &Shader::link() {
    glLinkProgram(shader_program_id);

    GLint success; GLchar error_log[512];
    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program_id, 512, NULL, error_log);
        throw ShaderLinkException(std::string(error_log));
    }
    
    return *this;
}

void Shader::use() {
    glUseProgram(shader_program_id);
}

void Shader::unuse() {}

GLuint Shader::uniform(std::string uniform) {
    return glGetUniformLocation(shader_program_id, uniform.c_str());
}
