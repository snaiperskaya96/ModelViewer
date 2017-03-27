//
// Created by Jury Verrigni on 3/27/17.
//

#ifndef MODELVIEWER_VECTOR4_H
#define MODELVIEWER_VECTOR4_H

#include "Vector3.h"

struct Vector4 {
    float X, Y, Z, W;

    Vector4(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 1.0f) : X(X), Y(Y), Z(Z), W(W) {}
    Vector4(Vector3 Vector = Vector3(), float W = 1.0f) : X(Vector.X), Y(Vector.Y), Z(Vector.Z), W(W) {}
};


#endif //MODELVIEWER_VECTOR4_H
