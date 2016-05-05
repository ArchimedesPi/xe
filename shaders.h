#ifndef __SHADER_H__
#define __SHADER_H__

class Shader {
public:
    ~Shader();

    static Shader fromFile(std::string path, GLenum shader_type_);
    static Shader fromString(std::string code, GLenum shader_type_);

    GLuint shader_id;
    GLenum shader_type;
private:
    Shader(std::string code, GLenum shader_type_);
};

class ShaderProgram {
public:
    ShaderProgram();

    ShaderProgram &addShader(Shader shader);
    ShaderProgram &link();

    void use();
    GLuint uniform(std::string uniform);

    GLuint shader_program_id;
};

#endif
