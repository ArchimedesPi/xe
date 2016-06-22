#include <iostream>
#include <functional>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "scenegraph.h"

SceneNode::SceneNode() {}

SceneNode::~SceneNode() {
    for (int i=0; i<children.size(); i++) {
        delete children[i];
    }
    children.clear();
}

void SceneNode::addChild(SceneNode *child) {
    children.push_back(child);
    child->parent = this;
}

void SceneNode::computeTransforms() {
    local_matrix = glm::translate(glm::mat4(), glm::vec3(x,y,z))
        * glm::yawPitchRoll(yaw, pitch, roll)
        * custom_matrix;

    if (parent != NULL) {
        world_matrix = parent->world_matrix * local_matrix;
    } else {
        world_matrix = local_matrix;
    }
}

void SceneNode::computeBackTransforms() {
    if (parent != NULL) parent->computeBackTransforms();
    computeTransforms();
}

void SceneNode::computeDependantTransforms() {
    computeTransforms();

    std::for_each(children.begin(),
            children.end(),
            std::mem_fun(&SceneNode::computeTransforms));
}

std::ostringstream SceneNode::dumpTransforms() {
    std::ostringstream s; s << "scene node (" << this << ", parent:" << this->parent << ") transforms:\n" \
        << "\tlocal: " << glm::to_string(local_matrix) \
        << "\n\tworld: " << glm::to_string(world_matrix) \
        << std::endl;
    return s;
}

std::ostringstream SceneNode::dumpParameters() {
    std::ostringstream s; s << "scene node (" << this << ", parent:" << this->parent << ") properties:\n" \
        << "\tx:" << this->x \
        << " y:" << this->y \
        << " z:" << this->z \
        << "\n\troll:" << this->roll \
        << " pitch:" << this->pitch \
        << " yaw:" << this->yaw \
        << std::endl;
    return s;
}

