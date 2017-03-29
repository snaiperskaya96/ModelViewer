//
// Created by Jury Verrigni on 3/29/17.
//

#include "MeshComponent.h"

void MeshComponent::SetFaces(std::vector< std::vector<int> > Faces) {
    this->Faces = Faces;
}

void MeshComponent::SetPoints(std::vector<float> Points) {
    this->Points = Points;
}
