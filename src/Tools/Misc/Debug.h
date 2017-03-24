//
// Created by Jury Verrigni on 3/24/17.
//

#ifndef MODELVIEWER_DEBUG_H
#define MODELVIEWER_DEBUG_H


#include <GL/glew.h>

class Debug {
public:
    static void PrintGlLog(bool ToFile = true);
    static bool GlLog(const char* Message, ...);
    static void PrintProgrammeInfoLog(GLuint ProgrammeReference);
    static bool IsProgrammeValid(GLuint ProgrammeReference) ;

};


#endif //MODELVIEWER_DEBUG_H
