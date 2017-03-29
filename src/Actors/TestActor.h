//
// Created by Jury Verrigni on 3/28/17.
//

#ifndef MODELVIEWER_TRIANGLE_H
#define MODELVIEWER_TRIANGLE_H


#include <Components/MeshComponent.h>
#include "Actor.h"

class TestActor : public Actor {
public:
    TestActor();

    void Init() override;

    const float *GetPoints(int &Size) override;

private:
public:
    void Update() override;

private:
public:
    const char *GetShaderVertexName() override;

    const char *GetShaderFragmentName() override;

private:
    MeshComponent* Mesh;
    GLuint ElementsBufferObject = 0;
};


#endif //MODELVIEWER_TRIANGLE_H
