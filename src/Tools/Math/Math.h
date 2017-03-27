//
// Created by Jury Verrigni on 3/27/17.
//

#ifndef MODELVIEWER_MATH_H
#define MODELVIEWER_MATH_H

#include "Vector3.h"
#include "Matrix4.h"

class Math {
public:
    static Matrix4 Translate (const Matrix4& Matrix, const Vector3 &Vector);
};


#endif //MODELVIEWER_MATH_H
