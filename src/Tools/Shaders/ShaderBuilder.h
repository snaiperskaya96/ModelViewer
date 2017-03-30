//
// Created by Jury Verrigni on 3/23/17.
//

#ifndef MODELVIEWER_SHADERBUILDER_H
#define MODELVIEWER_SHADERBUILDER_H


#include <GL/glew.h>
#include <vector>

struct ShaderProgramme {
    const GLuint ProgrammeId;
    const GLuint VertexId;
    const GLuint FragmentId;
    const char* VertexFileName;
    const char* FragmentFileName;

    ShaderProgramme(GLuint ProgrammeId, GLuint VertexId, GLuint FragmentId, const char* VertexFileName, const char* FragmentFileName) :
        ProgrammeId(ProgrammeId), VertexId(VertexId), FragmentId(FragmentId), VertexFileName(VertexFileName), FragmentFileName(FragmentFileName) {}

    bool operator==(const ShaderProgramme &A) {
        return A.VertexFileName == VertexFileName && A.FragmentFileName == FragmentFileName;
    }
};

struct Shader {
    const GLuint ShaderId;
    const char* Name;
    const GLenum ShaderType;

    Shader(GLuint ShaderId, const char* Name, GLenum ShaderType) : ShaderId(ShaderId), Name(Name), ShaderType(ShaderType) {}

    bool operator==(const Shader &A) {
        return A.ShaderType == ShaderType && A.Name == Name;
    }
};

class ShaderBuilder {
public:
    static ShaderBuilder& GetInstance()
    {
        static ShaderBuilder instance;
        return instance;
    }
    bool DebugShaders = false;
private:
    std::vector<ShaderProgramme> ShaderProgrammeList;
    std::vector<Shader> ShaderList;
    ShaderBuilder() {};

public:
    GLuint BuildShader(GLenum ShaderType, const char* ShaderName);
    bool CreateProgramme(GLuint Vertex, GLuint Fragment, GLuint* Programme);
    GLuint CreateProgrammeFromFiles(const char *VertexFileName, const char *FragmentFileName);
    ShaderBuilder(ShaderBuilder const&) = delete;
    void operator=(ShaderBuilder const&) = delete;
};


#endif //MODELVIEWER_SHADERBUILDER_H
