//
// Created by Jury Verrigni on 3/27/17.
//

#include <math.h>
#include "Math.h"

Matrix4 Math::Translate(const Matrix4 &Matrix, const Vector3 &Vector) {
    Matrix4 TranslationMatrix = Matrix4::IdentityMatrix();
    TranslationMatrix.Matrix[12] = Vector.X;
    TranslationMatrix.Matrix[13] = Vector.Y;
    TranslationMatrix.Matrix[14] = Vector.Z;
    return TranslationMatrix * Matrix;
}

Matrix4 Math::RotateYDeg(const Matrix4 &Matrix, const float Degrees) {
    float Radiants = (float) (Degrees * ONE_DEG_IN_RAD);
    Matrix4 NewMatrix = Matrix4::IdentityMatrix ();
    NewMatrix.Matrix[0] = (float) cos (Radiants);
    NewMatrix.Matrix[8] = (float) sin (Radiants);
    NewMatrix.Matrix[2] = (float) -sin (Radiants);
    NewMatrix.Matrix[10] = (float) cos (Radiants);
    return NewMatrix * Matrix;

}
