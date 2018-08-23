//
// Created by jan on 22.08.18.
//

#include "Scene.h"

Scene::~Scene() {
    for(auto object : objects){
        delete object;
    }
}

void Scene::addObject(Intersectable* intersectable) {
    objects.push_back(intersectable);
}

Scene::Scene() {

}

Vector3f Scene::intersect(Ray ray) {
    return Vector3f();
}

bool Scene::intersects(Ray ray) {
    for(Intersectable* intersectable : objects){
        if (intersectable->intersects(ray)) {
            return true;
        }
    }
    return false;
}
