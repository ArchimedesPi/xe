#include <vector>

#include "scene.h"

void Scene::addObject(GameObject *object) {
    objects.push_back(object);
}
