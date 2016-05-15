#include <glm/gtc/type_ptr.hpp>
#include "camera.h"

glm::mat4 Camera::lookMatrix() {
    if (dirty) {
        computeMatrix();
    }
    return this->look_matrix;
}

const GLfloat* Camera::lookMatrixGl() {
    return glm::value_ptr(this->lookMatrix());
}

void Camera::lookAt(glm::vec3 position) {
    this->look = position;
    this->dirty = true;
}

void Camera::lookInDirection(glm::vec3 direction) {
    this->look = this->eye + direction;
    this->dirty = true;
}

void Camera::setEye(glm::vec3 position) {
    this->eye = position;
    this->dirty = true;
}

void Camera::computeMatrix() {
    this->look_matrix = glm::lookAt(this->eye,
            this->look,
            this->up);
    this->dirty = false;
}
