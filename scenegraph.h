#ifndef __SCENEGRAPH_H__
#define __SCENEGRAPH_H__

#include <sstream>
#include <vector>
#include <glm/glm.hpp>

class SceneNode {
public:
    SceneNode();
    virtual ~SceneNode();

    void addChild(SceneNode *child);

    void computeTransforms();
    void computeBackTransforms();
    void computeDependantTransforms();

    std::ostringstream dumpTransforms();
    std::ostringstream dumpParameters();

    glm::mat4 local_matrix;
    glm::mat4 custom_matrix = glm::mat4();
    glm::mat4 world_matrix;

    float x=0, y=0, z=0;
    float roll=0, pitch=0, yaw=0;

    SceneNode *parent = NULL;
    std::vector<SceneNode*> children;
};

#endif
