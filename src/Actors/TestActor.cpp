//
// Created by Jury Verrigni on 3/28/17.
//

#include <Tools/Mesh/ObjImporter.h>
#include <Tools/Shaders/ShaderBuilder.h>
#include "TestActor.h"

TestActor::TestActor() : Actor() {
    //Mesh = ObjImporter::CreateMeshFromFileName("/tmp/cube.obj");
    GLfloat colours[] = {	1.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f,
                             0.0f, 0.0f, 1.0f };
    std::vector<int> faces = {0,1,2};
    std::vector<float> points = {	-0.3f, 0.5f, -0.0f,
                                   -0.8f, -0.5f, 0.0f,
                                   0.2f, -0.5f, 0.0f };

    Mesh = new MeshComponent;
    Mesh->SetFaces(faces);
    Mesh->SetPoints(points);
}

const float *TestActor::GetPoints(int &Size) {
    return Mesh->GetPoints(Size);
}

void TestActor::Update() {
    int NumOfFaces;
    const int* Faces = Mesh->GetFaces(NumOfFaces);
    int NumVerticles;
    const float* Verticles = Mesh->GetPoints(NumVerticles);

    glUseProgram(ShaderProgramme);
    glBindVertexArray(LocalVertexArrayObject);

    glDrawArrays(GL_TRIANGLES, 0, NumVerticles);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementsBufferObject);

    //glDrawElements(GL_TRIANGLES, Num, GL_UNSIGNED_INT, NULL);
}

const char *TestActor::GetShaderVertexName() {
    return "test";
}

const char *TestActor::GetShaderFragmentName() {
    return "test";
}

void TestActor::Init() {
    int NumOfVerticles = 24;
    const float* Verticles = GetPoints(NumOfVerticles);
    int NumOfFaces = 0;
    const int* Faces = Mesh->GetFaces(NumOfFaces);


    glGenVertexArrays(1, &LocalVertexArrayObject);
    glBindVertexArray(LocalVertexArrayObject);

    GLuint VertexBufferObject = 0;
    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, NumOfVerticles * sizeof(GL_FLOAT), Verticles, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ElementsBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementsBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumOfVerticles * sizeof(GL_INT), Faces, GL_STATIC_DRAW);


    ShaderProgramme = ShaderBuilder::GetInstance().CreateProgrammeFromFiles("test", "test");
}
