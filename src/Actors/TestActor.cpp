//
// Created by Jury Verrigni on 3/28/17.
//

#include <Tools/Mesh/ObjImporter.h>
#include <Tools/Shaders/ShaderBuilder.h>
#include "TestActor.h"

TestActor::TestActor() : Actor() {
	//Mesh = ObjImporter::CreateMeshFromFileName("ObjMeshes/Lamp.obj");
	Mesh = ObjImporter::CreateMeshFromFileName("ObjMeshes/Cube.obj");
}

const float *TestActor::GetPoints(int &Size) {
    return Mesh->GetPoints(Size);
}

void TestActor::Update() {
    int NumOfFaces;
    //const int* Faces = Mesh->GetFaces(NumOfFaces);
    int NumVerticles;
    const float* Verticles = Mesh->GetPoints(NumVerticles);

    glUseProgram(ShaderProgramme);
    glBindVertexArray(LocalVertexArrayObject);

    //glDrawArrays(GL_TRIANGLES, 0, 3);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementsBufferObject);

	for (std::vector<int> Faces : Mesh->GetFacesVector()) {
		//if (Faces.size() % 3 == 0) {
			for (int i = 0; i < Faces.size() / 3; i ++) {
				glDrawRangeElements(GL_LINES, i * 3, i * 3 + 3, 3, GL_UNSIGNED_INT, &Faces[i]);
			}
		//} else {
		//	glDrawElements(GL_POLYGON, Faces.size(), GL_UNSIGNED_INT, &Faces[0]);
		//}
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
    //const int* Faces = Mesh->GetFaces(NumOfFaces);


    glGenVertexArrays(1, &LocalVertexArrayObject);
    glBindVertexArray(LocalVertexArrayObject);
	glEnableVertexAttribArray(0);


    GLuint VertexBufferObject = 0;
    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, NumOfVerticles * sizeof(float), Verticles, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //glGenBuffers(1, &ElementsBufferObject);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementsBufferObject);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumOfVerticles * sizeof(int), Faces, GL_STATIC_DRAW);

    ShaderProgramme = ShaderBuilder::GetInstance().CreateProgrammeFromFiles("test", "test");
}
