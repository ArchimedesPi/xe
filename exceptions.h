#ifndef __XE_EXCEPTIONS__
#define __XE_EXCEPTIONS__
#include <exception>
using namespace std;

class ShaderCompileException : public exception {
private:
    string message_;
public:
    explicit ShaderCompileException(const std::string& message) : message_(message) {}
    virtual const char* what() const throw() {
        return ("Error compiling shader: " + message_).c_str();
    }
};

class ShaderLinkException : public exception {
private:
    string message_;
public:
    explicit ShaderLinkException(const std::string& message) : message_(message) {}
    virtual const char* what() const throw() {
        return ("Error linking shaders: " + message_).c_str();
    }
};

#endif
