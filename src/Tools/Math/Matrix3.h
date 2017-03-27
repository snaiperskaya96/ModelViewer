//
// Created by Jury Verrigni on 3/27/17.
//

#ifndef MODELVIEWER_MATRIX_H
#define MODELVIEWER_MATRIX_H

/**
 * 0 3 6
 * 1 4 7
 * 2 5 8
 */

struct Matrix3 {
    Matrix3() {
        for (short i = 0; i < 9; i++) {
            Matrix[i] = 0.f;
        }
    };

    Matrix3(
            float A = 0.0f, float B = 0.0f, float C = 0.0f, float D = 0.0f, float E = 0.0f,
            float F = 0.0f, float G = 0.0f, float H = 0.0f, float I = 0.0f
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
    }

    float Matrix[9];
};


#endif //MODELVIEWER_MATRIX_H
