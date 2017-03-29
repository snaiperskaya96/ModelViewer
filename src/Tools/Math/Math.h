//
// Created by Jury Verrigni on 3/27/17.
//

#ifndef MODELVIEWER_MATH_H
#define MODELVIEWER_MATH_H

#include "Vector3.h"
#include "Matrix4.h"
#include <math.h>

#define _USE_MATH_DEFINES
#include <cmath> 

#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444
#define ONE_RAD_IN_DEG 360.0 / (2.0 * M_PI) //57.2957795

class Math {
public:
    static Matrix4 Translate (const Matrix4& Matrix, const Vector3 &Vector);
    static Matrix4 RotateYDeg(const Matrix4& Matrix, const float Degrees);
};


#endif //MODELVIEWER_MATH_H
