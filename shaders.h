#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>
#include <string>

class ShaderFile {
public:
    ~ShaderFile();

    static ShaderFile fromFile(std::string path, GLenum shader_type_);
    static ShaderFile fromString(std::string code, GLenum shader_type_);

    GLuint shader_id;
    GLenum shader_type;
private:
    ShaderFile(std::string code, GLenum shader_type_);
};

class Shader {
public:
    Shader();

    Shader &loadFromManifest(std::string path);

    // deprecated for public use. manifests are better.
    Shader &addShaderFile(ShaderFile shader);

    Shader &link();

    void use();
    void unuse();
    GLuint uniform(std::string uniform);

    std::string display_name;
private:
    GLuint shader_program_id;
};

#endif
