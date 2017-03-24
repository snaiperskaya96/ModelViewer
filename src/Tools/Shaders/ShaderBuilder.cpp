#include <fstream>
#include <iostream>
#include <Misc/Debug.h>
#include <assert.h>
#include "ShaderBuilder.h"

GLuint ShaderBuilder::BuildShader(GLenum ShaderType, const char* ShaderName) {
    const char* Directory;

    if (ShaderType == GL_VERTEX_SHADER) {
        Directory = "/Users/juryverrigni/ClionProjects/ModelViewer/src/Shaders/Vertex/";
    } else {
        Directory = "/Users/juryverrigni/ClionProjects/ModelViewer/src/Shaders/Fragment/";
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

    GLuint Shader = glCreateShader(ShaderType);
    const char* ShaderCharArray = ShaderText.c_str();

    glShaderSource(Shader, 1, &ShaderCharArray, NULL);
    glCompileShader(Shader);

    return Shader;
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
    GLuint Vertex, Fragment, Programme;
    Vertex = BuildShader (GL_VERTEX_SHADER, VertexFileName);
    Fragment = BuildShader (GL_FRAGMENT_SHADER, FragmentFileName);
    assert (CreateProgramme(Vertex, Fragment, &Programme));
    return Programme;
}