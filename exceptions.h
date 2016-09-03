#pragma once

#include <exception>

class ShaderCompileException : public std::runtime_error {
public:
    explicit ShaderCompileException(const std::string& message)
        : std::runtime_error("Error compiling shader: " + message) {}
};

class ShaderLinkException : public std::runtime_error {
public:
    explicit ShaderLinkException(const std::string& message)
        : std::runtime_error("Error linking shaders: " + message) {}
};
