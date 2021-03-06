//
// Created by Jury Verrigni on 3/29/17.
//

#ifndef MODELVIEWER_MESH_H
#define MODELVIEWER_MESH_H

#include <vector>

class MeshComponent {
public:
    void SetPoints(std::vector<float> Points);
    void SetFaces(std::vector< std::vector<int> > Faces);
	void SetRawFaces(std::vector<int> Faces);

    void Optimise();

	const std::vector< std::vector<int> > GetFacesVector() { return Faces; };
	const float* GetPoints(int& Size) { Size = Points.size(); return &Points[0]; }
    const int* GetFaces(int& Size) { Size = RawFaces.size(); return &RawFaces[0]; }

private:
    std::vector<float> Points;
	std::vector< std::vector<int> > Faces;
	std::vector<int> RawFaces;
};


#endif //MODELVIEWER_MESH_H
