#include <fstream>
#include <iostream>
#include <Misc/Debug.h>
#include <assert.h>
#include "ShaderBuilder.h"

GLuint ShaderBuilder::BuildShader(GLenum ShaderType, const char* ShaderName) {
    for (Shader &S : ShaderList) {
        if (S.Name == ShaderName && S.ShaderType == ShaderType) {
            return S.ShaderId;
        }
    }
    const char* Directory;

    if (ShaderType == GL_VERTEX_SHADER) {
        Directory = "Shaders/Vertex/";
    } else {
        Directory = "Shaders/Fragment/";
    }

    std::string Path = Directory;
    Path += ShaderName;
    Path += ".glsl";

    std::ifstream File(Path);
    std::string FileRow;
    std::string ShaderText;
    while (std::getline(File, FileRow)) {
        ShaderText += FileRow + "\n";
    }

    if (DebugShaders) {
        Debug::GlLog("Compiling shader %s (Type: %u):\n", ShaderName, ShaderType);
        Debug::GlLog(ShaderText.c_str());
    }

    GLuint S = glCreateShader(ShaderType);
    const char* ShaderCharArray = ShaderText.c_str();

    glShaderSource(S, 1, &ShaderCharArray, NULL);
    glCompileShader(S);

    ShaderList.push_back(Shader(S, ShaderName, ShaderType));

    return S;
}

bool ShaderBuilder::CreateProgramme(GLuint Vertex, GLuint Fragment, GLuint *Programme) {
    *Programme = glCreateProgram ();
    Debug::GlLog (
            "created Programme %u. attaching shaders %u and %u...\n",
            *Programme,
            Vertex,
            Fragment
    );
    glAttachShader (*Programme, Vertex);
    glAttachShader (*Programme, Fragment);
    // link the shader Programme. if binding input attributes do that before link
    glLinkProgram (*Programme);
    GLint params = -1;
    glGetProgramiv (*Programme, GL_LINK_STATUS, &params);
    if (GL_TRUE != params) {
        Debug::GlLog (
                "ERROR: could not link shader Programme GL index %u\n",
                *Programme
        );
        Debug::PrintProgrammeInfoLog (*Programme);
        return false;
    }
    assert (Debug::IsProgrammeValid(*Programme));
    // delete shaders here to free memory
    glDeleteShader (Vertex);
    glDeleteShader (Fragment);

    return true;
}

GLuint ShaderBuilder::CreateProgrammeFromFiles(const char *VertexFileName, const char *FragmentFileName) {
    for (ShaderProgramme &P : ShaderProgrammeList) {
        if (P.VertexFileName == VertexFileName && P.FragmentFileName == FragmentFileName) {
            return P.ProgrammeId;
        }
    }

    GLuint Vertex, Fragment, Programme;
    Vertex = BuildShader (GL_VERTEX_SHADER, VertexFileName);
    Fragment = BuildShader (GL_FRAGMENT_SHADER, FragmentFileName);

    assert (CreateProgramme(Vertex, Fragment, &Programme));

    ShaderProgrammeList.push_back(ShaderProgramme(Programme, Vertex, Fragment, VertexFileName, FragmentFileName));

    return Programme;
}