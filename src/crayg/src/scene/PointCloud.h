//
// Created by Jan Honsbrok on 02.01.20.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_POINTCLOUD_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_POINTCLOUD_H_

#include "SceneObject.h"
class PointCloud : public SceneObject {
 public:
    bool isIntersecting(Ray ray) override;
    Vector3f getNormal(Vector3f point) override;
    Intersection intersect(Ray ray) override;

    void serialize(Serializer &serializer) override;
    void deserialize(Deserializer &deserializer) override;

    const std::vector<Vector3f> &getPoints() const;
    void setPoints(const std::vector<Vector3f> &points);
    const std::vector<float> &getRadii() const;
    void setRadii(const std::vector<float> &radii);
 private:
    std::vector<Vector3f> points;
    std::vector<float> radii;
};

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_POINTCLOUD_H_
