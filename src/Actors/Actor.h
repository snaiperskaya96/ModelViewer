//
// Created by Jury Verrigni on 3/27/17.
//

#ifndef MODELVIEWER_ACTOR_H
#define MODELVIEWER_ACTOR_H


#include <ModelViewer.h>

class Actor {
public:
    Actor();

private:
    Vector3 ActorLocation;
    Matrix4 TranslationMatrix;
    Matrix4 RotationMatrix;

public:
    void SetActorLocation(Vector3 NewLocation);
    Vector3 GetActorLocation();
};


#endif //MODELVIEWER_ACTOR_H
