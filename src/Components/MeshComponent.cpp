//
// Created by Jury Verrigni on 3/29/17.
//
#define NUMBER_TRIALS 1
#define TETLIBRARY

#include <iostream>
#include <tetgen.h>
#include "MeshComponent.h"
#include "tetgen.h"

void MeshComponent::SetFaces(std::vector< std::vector<int> > Faces) {
    this->Faces = Faces;
}

void MeshComponent::SetPoints(std::vector<float> Points) {
    this->Points = Points;
}

void MeshComponent::SetRawFaces(std::vector<int> Faces) {
    this->RawFaces = Faces;
}

void MeshComponent::Optimise() {
}
