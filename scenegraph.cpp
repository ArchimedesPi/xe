#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "scenegraph.h"

Node::Node() {}

virtual Node::~Node() {
    std::for_each(children.begin(),
            children.end(),
            std::mem_fun(&Node::~Node));
    children.clear();
}

void Node::addChild(Node *child) {
    children.push_back(child);
}

void Node::computeLocalTransforms() {
    local_matrix = glm::translate(local_matrix, glm::vec3(x,y,z));
    local_matrix *= glm::gtx::euler_angles(yaw, pitch, roll);
    world_matrix = local_matrix * parent->world_matrix;
}

void Node:computeAllTransforms() {
    computeLocalTransforms();

    std::for_each(children.begin(),
            children.end(),
            std::mem_fun(&Node::computeLocalTransforms));
}
