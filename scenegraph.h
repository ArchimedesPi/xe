#ifndef __SCENEGRAPH_H__
#define __SCENEGRAPH_H__

#include <list>
#include <glm/glm.hpp>

class Node {
public:
    Node();
    virtual ~Node();

    void addChild(Node *child);

    void computeLocalTransforms();
    void computeAllTransforms();

    glm::mat4 local_matrix;
    glm::mat4 world_matrix;

    float x=0, y=0, z=0;
    float roll=0, pitch=0, yaw=0;

    Node *parent;
    std::list<Node*> children;
};

#endif
