//
// Created by Jury Verrigni on 3/24/17.
//

#ifndef MODELVIEWER_DEBUG_H
#define MODELVIEWER_DEBUG_H

#include "ModelViewer.h"

class Debug {
public:
    static void PrintGlLog(bool ToFile = true);
    static bool GlLog(const char* Message, ...);
    static void PrintProgrammeInfoLog(GLuint ProgrammeReference);
    static bool IsProgrammeValid(GLuint ProgrammeReference) ;
    static void Init();
    static void GlDebugMessageCallback(GLenum Source, GLenum Type, GLuint Id, GLenum Severity, GLsizei Length, const GLchar* Message, const void* UserParam);
    static void GlfwErrorCallback(int Error, const char* Description);
};


#endif //MODELVIEWER_DEBUG_H
