//
// Created by Jury Verrigni on 3/27/17.
//

#ifndef MODELVIEWER_VECTOR3_H
#define MODELVIEWER_VECTOR3_H

struct Vector3 {
    float X, Y, Z;

    Vector3(float X = 0.0f, float Y = 0.0f, float Z = 0.0f) : X(X), Y(Y), Z(Z) {}

    Vector3 operator* (Vector3 Vector) {
        Vector3 NewVector;
        NewVector.X = Y * Vector.Z - Z * Vector.Y;
        NewVector.Y = Z * Vector.X - X * Vector.Z;
        NewVector.Z = X * Vector.Y - Y * Vector.X;
        return NewVector;
    }

    Vector3 operator* (float Value) {
        return Vector3(X * Value, Y * Value, Z * Value);
    }

    float ScalarProduct(Vector3 Vector) {
        return X * Vector.X + Y * Vector.Y + Z + Vector.Z;
    }
};

#endif //MODELVIEWER_VECTOR3_H
