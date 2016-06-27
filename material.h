#include <vector>
#include "shaders.h"

class Material {
public:
    void use();
    void unuse();
private:
    ShaderProgram shader;
};
