//
// Created by Jury Verrigni on 3/27/17.
//

#ifndef MODELVIEWER_MATRIX4_H
#define MODELVIEWER_MATRIX4_H

#include "Vector4.h"

struct Matrix4 {
    Matrix4(
            float A = 0.0f, float B = 0.0f, float C = 0.0f, float D = 0.0f,
            float E = 0.0f, float F = 0.0f, float G = 0.0f, float H = 0.0f,
            float I = 0.0f, float J = 0.0f, float K = 0.0f, float L = 0.0f,
            float M = 0.0f, float N = 0.0f, float O = 0.0f, float P = 0.0f
    ) {
        Matrix[0] = A;
        Matrix[1] = B;
        Matrix[2] = C;
        Matrix[3] = D;
        Matrix[4] = E;
        Matrix[5] = F;
        Matrix[6] = G;
        Matrix[7] = H;
        Matrix[8] = I;
        Matrix[9] = J;
        Matrix[10] = K;
        Matrix[11] = L;
        Matrix[12] = M;
        Matrix[13] = N;
        Matrix[14] = O;
        Matrix[15] = P;
    }

    Vector4 operator* (const Vector4& Vector) {
        float X = Matrix[0] * Vector.X +
                    Matrix[4] * Vector.Y +
                    Matrix[8] * Vector.Z +
                    Matrix[12] * Vector.W;
        float Y = Matrix[1] * Vector.X +
                    Matrix[5] * Vector.Y +
                    Matrix[9] * Vector.Z +
                    Matrix[13] * Vector.W;
        float Z = Matrix[2] * Vector.X +
                    Matrix[6] * Vector.Y +
                    Matrix[10] * Vector.Z +
                    Matrix[14] * Vector.W;
        float W = Matrix[3] * Vector.X +
                    Matrix[7] * Vector.Y +
                    Matrix[11] * Vector.Z +
                    Matrix[15] * Vector.W;
        return Vector4 (X, Y, Z, W);
    }

    static Matrix4 IdentityMatrix()
    {
        return Matrix4(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    Matrix4 operator* (const Matrix4 &Matrix)
    {
        Matrix4 NewMatrix;
        int Index = 0;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                float sum = 0.0f;
                for (int i = 0; i < 4; i++) {
                    sum += Matrix.Matrix[i + col * 4] * this->Matrix[row + i * 4];
                }
                NewMatrix.Matrix[Index] = sum;
                Index++;
            }
        }
        return NewMatrix;
    }

    float Matrix[16];
};

#endif //MODELVIEWER_MATRIX4_H
