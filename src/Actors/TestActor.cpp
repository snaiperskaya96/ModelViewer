//
// Created by Jury Verrigni on 3/28/17.
//

#include <Tools/Mesh/ObjImporter.h>
#include <Tools/Shaders/ShaderBuilder.h>
#include "TestActor.h"

TestActor::TestActor() : Actor() {
	//Mesh = ObjImporter::CreateMeshFromFileName("ObjMeshes/Lamp.obj");
	Mesh = ObjImporter::CreateMeshFromFileName("ObjMeshes/Cube.obj");
    /*
    Mesh = new MeshComponent();
    Mesh->SetPoints(std::vector<float>({
             		-0.5f, -0.5f, 0.0f,
             		0.5f, -0.5f, 0.0f,
             		0.5f, 0.5f, 0.0f,
             		-0.5f, 0.5f, 0.0f
             	}));
    std::vector< std::vector<int> > faces;
    faces.push_back(std::vector<int> ({
        0, 1, 2
                                      }));
    faces.push_back(std::vector<int> ({
        2, 3, 0
                                      }));
    Mesh->SetFaces(faces);
     */
}

const float *TestActor::GetPoints(int &Size) {
    return Mesh->GetPoints(Size);
}

void TestActor::Update() {
    glUseProgram(ShaderProgramme);
    glBindVertexArray(LocalVertexArrayObject);

	for (std::vector<int> Faces : Mesh->GetFacesVector()) {
        glDrawElements(GL_LINE_LOOP, (GLsizei) Faces.size(), GL_UNSIGNED_INT, &Faces[0]);
	}

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


    VertexBufferObject = 0;
    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, NumOfVerticles * sizeof(float), Verticles, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLuint ElementsBufferObject;
    glGenBuffers(1, &ElementsBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementsBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumOfFaces * sizeof(int), Faces, GL_STATIC_DRAW);

    ShaderProgramme = ShaderBuilder::GetInstance().CreateProgrammeFromFiles("test", "test");
}
