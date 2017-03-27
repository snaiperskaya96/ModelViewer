//
// Created by Jury Verrigni on 3/27/17.
//

#ifndef MODELVIEWER_CAMERA_H
#define MODELVIEWER_CAMERA_H


#include "Actors/Actor.h"

class Camera : public Actor {
public:
    Camera();
private:
    float CameraSpeed = 1.0f;
    float CameraYawSpeed = 10.0f;

};


#endif //MODELVIEWER_CAMERA_H
