//
// Created by Jury Verrigni on 3/27/17.
//

#ifndef MODELVIEWER_CAMERA_H
#define MODELVIEWER_CAMERA_H


#include <Math/Math.h>
#include "Actor.h"


class Camera : public Actor {
public:
    Camera();
    void Init() override;
    void Update() override;
private:
    float CameraSpeed = 1.0f;
    float CameraYawSpeed = 10.0f;
    float NearDistance = 0.1f;
    float FarDistance = 100.f;
    float FieldOfView = (float) ((float) (67.0f * ONE_DEG_IN_RAD));
    float AspectRatio;

};


#endif //MODELVIEWER_CAMERA_H
