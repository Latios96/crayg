//
// Created by Jan Honsbrok on 12.11.18.
//

#include "Triangle.h"

Triangle::Intersection Triangle::intersect(Ray ray) {
    Vector3f normal = (v1 - v0).crossProduct((v2 - v0)).normalize();

    const float scalar = normal.scalarProduct(ray.direction);

    const bool raysAreParallel = scalar == 0;
    auto angleBetweenVectorsAsRadiant = scalar / (normal.length() * ray.direction.length());
    const bool isBackFacing = angleBetweenVectorsAsRadiant > 0;

    if(raysAreParallel){
        return {std::numeric_limits<float>::max(), nullptr};
    }
    else{
        //const float t = - (normal.scalarProduct(ray.startPoint) + v0.length()) / scalar;
        float d = normal.scalarProduct(v0);

        const float t = - (normal.scalarProduct(ray.startPoint) + d) / scalar;

        if(t>0){
            Vector3f hitLocation = ray.startPoint + (ray.direction*t);

            Vector3f C;

            // do inside / outside test

            Vector3f edge0 = v1 - v0;
            Vector3f vp0 = hitLocation - v0;
            C = edge0.crossProduct(vp0);
            auto scal = normal.scalarProduct(C);
            if (scal < 0){
                return {std::numeric_limits<float>::max(), nullptr};
            }

            Vector3f edge1 = v2 - v1;
            Vector3f vp1 = hitLocation - v1;
            C = edge1.crossProduct(vp1);
            if (normal.scalarProduct(C)<0){
                return {std::numeric_limits<float>::max(), nullptr};
            }

            Vector3f edge2 = v0 - v2;
            Vector3f vp2 = hitLocation - v2;
            C = edge2.crossProduct(vp2);
            if (normal.scalarProduct(C)<0){
                return {std::numeric_limits<float>::max(), nullptr};
            }
            return {t, this};

        }
        return {std::numeric_limits<float>::max(), nullptr};
    }
}


bool Triangle::isIntersecting(Ray ray){
    Vector3f normal = (v1 - v0).crossProduct((v2 - v0));

    const float scalar = normal.scalarProduct(ray.direction);

    const bool raysAreParallel = scalar == 0;

    if(raysAreParallel){
        return false;
    }
    else{
        const float t = - (normal.scalarProduct(ray.startPoint) + v0.length()) / scalar;

        if(t>0){
            Vector3f hitLocation = ray.startPoint + (ray.direction*t);

            Vector3f C;

            // do inside / outside test

            Vector3f edge0 = v1 - v0;
            Vector3f vp0 = hitLocation - v0;
            C = edge0.crossProduct(vp0);
            if (normal.scalarProduct(C)<0){
                return false;
            }

            Vector3f edge1 = v2 - v1;
            Vector3f vp1 = hitLocation - v1;
            C = edge1.crossProduct(vp1);
            if (normal.scalarProduct(C)<0){
                return false;
            }

            Vector3f edge2 = v0 - v2;
            Vector3f vp2 = hitLocation - v2;
            C = edge2.crossProduct(vp2);
            if (normal.scalarProduct(C)<0){
                return false;
            }
            return true;

        }
        return false;
    }
}

Triangle::Triangle(const Vector3f v0, const Vector3f v1, const Vector3f v2) : v0(v0), v1(v1), v2(v2) {}

Triangle::Triangle() {
    v0 = Vector3f();
    v1 = Vector3f();
    v2 = Vector3f();
}

Vector3f Triangle::getNormal(Vector3f point) {
    const Vector3f normal = (v2 - v0).crossProduct(v1 - v0).normalize();
    return normal.invert();
}

