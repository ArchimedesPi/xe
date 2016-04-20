#ifndef __SHADER_H__
#define __SHADER_H__

GLuint load_shader_from_string(const char *shader_string, GLenum shader_type);
GLuint load_shader_from_file(const char *path, GLenum shader_type);

#endif
