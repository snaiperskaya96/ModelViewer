//
// Created by Jury Verrigni on 3/27/17.
//
#pragma once

#ifndef MODELVIEWER_ACTOR_H
#define MODELVIEWER_ACTOR_H


#include <ModelViewer.h>
#include <string>

class Actor {
public:
    Actor();
    const Matrix4 WorldSpaceMatrix;
    virtual void Init();
    virtual void Update();
private:
    Vector3 ActorLocation;
    Vector4 ActorRotation;
    Matrix4 TranslationMatrix;
    Matrix4 RotationMatrix;
    Matrix4 ViewMatrix;
protected:
    GLuint LocalVertexArrayObject = 0;
    GLuint ShaderProgramme = 0;
public:
    virtual const char* GetShaderVertexName();
    virtual const char* GetShaderFragmentName();
    virtual const float* GetPoints(int &Size);
public:
    virtual void SetActorLocation(Vector3 NewLocation);

    virtual Vector3 GetActorLocation();
};


#endif //MODELVIEWER_ACTOR_H
