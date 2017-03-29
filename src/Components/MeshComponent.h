//
// Created by Jury Verrigni on 3/29/17.
//

#ifndef MODELVIEWER_MESH_H
#define MODELVIEWER_MESH_H

#include <vector>

class MeshComponent {
public:
    void SetPoints(std::vector<float> Points);
    void SetFaces(std::vector<int> Faces);
    const float* GetPoints(int& Size) { Size = Points.size(); return &Points[0]; }
    const int* GetFaces(int& Size) { Size = Faces.size(); return &Faces[0]; }
private:
    std::vector<float> Points;
    std::vector<int> Faces;
};


#endif //MODELVIEWER_MESH_H
