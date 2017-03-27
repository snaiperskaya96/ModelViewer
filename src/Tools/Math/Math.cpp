//
// Created by Jury Verrigni on 3/27/17.
//

#include "Math.h"

Matrix4 Math::Translate(const Matrix4 &Matrix, const Vector3 &Vector) {
    Matrix4 TranslationMatrix = Matrix4::IdentityMatrix();
    TranslationMatrix.Matrix[12] = Vector.X;
    TranslationMatrix.Matrix[13] = Vector.Y;
    TranslationMatrix.Matrix[14] = Vector.Z;
    return TranslationMatrix * Matrix;
}
