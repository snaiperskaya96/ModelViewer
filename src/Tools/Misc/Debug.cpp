//
// Created by Jury Verrigni on 3/24/17.
//

#include <cstdarg>
#include <cstdio>
#include "Debug.h"

#define GL_LOG_FILE "gl.log"

void Debug::PrintGlLog(bool ToFile) {
    GLenum Params[] = {
            GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
            GL_MAX_CUBE_MAP_TEXTURE_SIZE,
            GL_MAX_DRAW_BUFFERS,
            GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
            GL_MAX_TEXTURE_IMAGE_UNITS,
            GL_MAX_TEXTURE_SIZE,
            GL_MAX_VARYING_FLOATS,
            GL_MAX_VERTEX_ATTRIBS,
            GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
            GL_MAX_VERTEX_UNIFORM_COMPONENTS,
            GL_MAX_VIEWPORT_DIMS,
            GL_STEREO,
    };
    const char* Names[] = {
            "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
            "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
            "GL_MAX_DRAW_BUFFERS",
            "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
            "GL_MAX_TEXTURE_IMAGE_UNITS",
            "GL_MAX_TEXTURE_SIZE",
            "GL_MAX_VARYING_FLOATS",
            "GL_MAX_VERTEX_ATTRIBS",
            "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
            "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
            "GL_MAX_VIEWPORT_DIMS",
            "GL_STEREO",
    };
    ToFile ? GlLog("GL Context Params:\n") : printf("GL Context Params:\n");
    char msg[256];
    // integers - only works if the order is 0-10 integer return types
    for (int i = 0; i < 10; i++) {
        int v = 0;
        glGetIntegerv(Params[i], &v);
        ToFile ? GlLog("%s %i\n", Names[i], v) : printf("%s %i\n", Names[i], v);
    }
    // others
    int v[2];
    v[0] = v[1] = 0;
    glGetIntegerv(Params[10], v);
    ToFile ? GlLog("%s %i %i\n", Names[10], v[0], v[1]) : printf("%s %i %i\n", Names[10], v[0], v[1]);
    unsigned char s = 0;
    glGetBooleanv(Params[11], &s);
    ToFile ? GlLog("%s %u\n", Names[11], (unsigned int)s) : printf("%s %u\n", Names[11], (unsigned int)s);
    ToFile ? GlLog("-----------------------------\n") : printf("-----------------------------\n");
}

bool Debug::GlLog(const char* Message, ...) {
    va_list argptr;
    FILE* file = fopen(GL_LOG_FILE, "a");
    if(!file) {
        fprintf(
                stderr,
                "ERROR: could not open GL_LOG_FILE %s file for appending\n",
                GL_LOG_FILE
        );
        return false;
    }
    va_start(argptr, Message);
    vfprintf(file, Message, argptr);
    va_end(argptr);
    fclose(file);
    return true;
}

void Debug::PrintProgrammeInfoLog(GLuint ProgrammeReference) {
    int max_length = 2048;
    int actual_length = 0;
    char log[2048];
    glGetProgramInfoLog (ProgrammeReference, max_length, &actual_length, log);
    printf ("program info log for GL index %u:\n%s", ProgrammeReference, log);
    GlLog ("program info log for GL index %u:\n%s", ProgrammeReference, log);
}

bool Debug::IsProgrammeValid(GLuint ProgrammeReference) {
    glValidateProgram (ProgrammeReference);
    GLint params = -1;
    glGetProgramiv (ProgrammeReference, GL_VALIDATE_STATUS, &params);
    if (GL_TRUE != params) {
        GlLog ("program %i GL_VALIDATE_STATUS = GL_FALSE\n", ProgrammeReference);
        PrintProgrammeInfoLog(ProgrammeReference);
        return false;
    }
    GlLog ("program %i GL_VALIDATE_STATUS = GL_TRUE\n", ProgrammeReference);
    return true;
}
