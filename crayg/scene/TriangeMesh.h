//
// Created by Jan Honsbrok on 13.11.18.
//

#ifndef CRAYG_TRIANGEMESH_H
#define CRAYG_TRIANGEMESH_H


#include <vector>
#include "SceneObject.h"
#include "Triangle.h"

class TriangleMesh : public SceneObject{
public:
    static void createCube(TriangleMesh &mesh){
        mesh.points.push_back({-1,-1, 1});
        mesh.points.push_back({1,-1, 1});
        mesh.points.push_back({-1,-1, -1});
        mesh.points.push_back({1,-1, -1});

        mesh.points.push_back({-1,1,1});
        mesh.points.push_back({1,1,1});
        mesh.points.push_back({-1,1,-1});
        mesh.points.push_back({1,1,-1});

        mesh.faceIndexes.push_back(0);
        mesh.faceIndexes.push_back(4);
        mesh.faceIndexes.push_back(5);

        mesh.faceIndexes.push_back(0);
        mesh.faceIndexes.push_back(5);
        mesh.faceIndexes.push_back(1);

        mesh.faceIndexes.push_back(1);
        mesh.faceIndexes.push_back(5);
        mesh.faceIndexes.push_back(7);

        mesh.faceIndexes.push_back(1);
        mesh.faceIndexes.push_back(7);
        mesh.faceIndexes.push_back(3);

        mesh.faceIndexes.push_back(2);
        mesh.faceIndexes.push_back(3);
        mesh.faceIndexes.push_back(6);

        mesh.faceIndexes.push_back(2);
        mesh.faceIndexes.push_back(3);
        mesh.faceIndexes.push_back(7);

        mesh.faceIndexes.push_back(2);
        mesh.faceIndexes.push_back(6);
        mesh.faceIndexes.push_back(7);

        mesh.faceIndexes.push_back(0);
        mesh.faceIndexes.push_back(2);
        mesh.faceIndexes.push_back(3);

        mesh.faceIndexes.push_back(0);
        mesh.faceIndexes.push_back(3);
        mesh.faceIndexes.push_back(1);

        mesh.faceIndexes.push_back(4);
        mesh.faceIndexes.push_back(6);
        mesh.faceIndexes.push_back(7);

        mesh.faceIndexes.push_back(7);
        mesh.faceIndexes.push_back(6);
        mesh.faceIndexes.push_back(5);
        /*mesh.points.push_back({0,0,0});
        mesh.points.push_back({0,1,0});
        mesh.points.push_back({1,0,0});

        mesh.faceIndexes.push_back(0);
        mesh.faceIndexes.push_back(1);
        mesh.faceIndexes.push_back(2);*/
    }

    Ray intersect(Ray ray) override;
    bool intersects(Ray ray) override;

    void serialize(Serializer& serializer) override;

    void deserialize(Deserializer& deserializer) override;

    Vector3f getNormal(Vector3f point) override;

    std::vector<Vector3f> points;
    std::vector<int> faceIndexes;

    void getTriangles(std::vector<Triangle> &triangles);
};


#endif //CRAYG_TRIANGEMESH_H
