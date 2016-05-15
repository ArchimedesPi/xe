#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera() : up(glm::vec3(0, 1, 0)) {}
    virtual ~Camera() {}

    glm::mat4 lookMatrix();
    const GLfloat* lookMatrixGl();

    void computeMatrix();

    void lookAt(glm::vec3 position);
    void lookInDirection(glm::vec3 direction);
    void setEye(glm::vec3 position);

    glm::vec3 eye;
    glm::vec3 look;
    glm::vec3 up;

protected:
    bool dirty; // dirty flag

    glm::mat4 look_matrix;
};

#endif
