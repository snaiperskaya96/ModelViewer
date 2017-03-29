//
// Created by Jury Verrigni on 3/27/17.
//

#include <Math/Math.h>
#include <cstdlib>
#include <GL/glew.h>
#include <Shaders/ShaderBuilder.h>
#include <cstring>
#include "Actor.h"

Actor::Actor()
{
    TranslationMatrix = Math::Translate(Matrix4::IdentityMatrix(), Vector3(-ActorLocation.X, -ActorLocation.Y, -ActorLocation.Z));
    RotationMatrix = Math::RotateYDeg(Matrix4::IdentityMatrix(), ActorRotation.Y);
    ViewMatrix = RotationMatrix * TranslationMatrix;
}

void Actor::SetActorLocation(Vector3 NewLocation)
{
    ActorLocation = NewLocation;
}

Vector3 Actor::GetActorLocation()
{
    return ActorLocation;
}

void Actor::Update() {
    float matrix[] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };

    glUseProgram(ShaderProgramme);
    glBindVertexArray(LocalVertexArrayObject);
    int Points;
    GetPoints(Points);
    glDrawElements(GL_TRIANGLES, Points, GL_UNSIGNED_INT, 0);
}

void Actor::Init() {
    int PointsSize;
    const float Colors[] = {
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
    };
    const float* Points = GetPoints(PointsSize);

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, PointsSize * sizeof(float), Points, GL_STATIC_DRAW);

    GLuint ColourVertexBufferObject = 0;
    glGenBuffers(1, &ColourVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, ColourVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors) * sizeof(float), Colors, GL_STATIC_DRAW); // Should be replaced


    glGenVertexArrays(1, &LocalVertexArrayObject);
    glBindVertexArray(LocalVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, ColourVertexBufferObject);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    if (strcmp(GetShaderFragmentName(), "base") == 0 && strcmp(GetShaderVertexName(), "base") == 0) {
        ShaderProgramme = ShaderBuilder::GetInstance().CreateProgrammeFromFiles("test", "test");
    }
}

const char* Actor::GetShaderFragmentName() {
    return "base";
}

const char* Actor::GetShaderVertexName() {
    return "base";
}

const float* Actor::GetPoints(int &Size) {
    /*
    static float Points[] = {
            -0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 1.0f,
            0.5f, 0.5f, 1.0f,
            0.5f, -0.5f, 1.0f,
            0.5f, -0.5f, 1.0f,
            -0.5f, -0.5f, 1.0f,
            -0.5f, 0.5f, 1.0f
    };
     */
    static float Points[] = {
            -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
            0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
            -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
    };
    Size = 6;
    return Points;
}


