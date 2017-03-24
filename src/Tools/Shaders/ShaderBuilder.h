//
// Created by Jury Verrigni on 3/23/17.
//

#ifndef MODELVIEWER_SHADERBUILDER_H
#define MODELVIEWER_SHADERBUILDER_H


#include <GL/glew.h>

class ShaderBuilder {
public:
    static GLuint BuildShader(GLenum ShaderType, const char* ShaderName);
    static bool CreateProgramme(GLuint Vertex, GLuint Fragment, GLuint* Programme);
    static GLuint CreateProgrammeFromFiles(const char *VertexFileName, const char *FragmentFileName);
};


#endif //MODELVIEWER_SHADERBUILDER_H
