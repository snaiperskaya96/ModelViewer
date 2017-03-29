//
// Created by Jury Verrigni on 3/24/17.
//

#include <cstdarg>
#include <cstdio>
#include "Debug.h"

#define GL_LOG_FILE "gl.log"

static const GLenum Params[] = {
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

static const char* Names[] = {
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

const char* SeverityString[] = {
        "severity: HIGH",
        "severity: MEDIUM",
        "severity: LOW"
};

static const char* SourceString[] = {
        "source: API",
        "source: WINDOW SYSTEM",
        "source: SHADER COMPILER",
        "source: THIRD PARTY",
        "source: APPLICATION",
        "source: OTHER"
};

static const char* TypeString[] = {
        "type: ERROR",
        "type: DEPRECATED BEHAVIOUR",
        "type: UNDEFINED BEHAVIOUR",
        "type: PORTABILITY",
        "type: PERFORMANCE",
        "type: OTHER"
};

void Debug::PrintGlLog(bool ToFile) {
    ToFile ? GlLog("GL Context Params:\n") : printf("GL Context Params:\n");

    const GLubyte* Renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* Version = glGetString (GL_VERSION); // version as a string

    ToFile ? GlLog("OpenGL Version: %s\nOpenGl Renderer: %s", Version, Renderer) : printf("OpenGL Version: %s\nOpenGl Renderer: %s", Version, Renderer);

    for (int i = 0; i < 10; i++) {
        int IntegerValue = 0;
        glGetIntegerv(Params[i], &IntegerValue);
        ToFile ? GlLog("%s %i\n", Names[i], IntegerValue) : printf("%s %i\n", Names[i], IntegerValue);
    }
    // others
    int IntegerValues[2];
    IntegerValues[0] = IntegerValues[1] = 0;
    glGetIntegerv(Params[10], IntegerValues);
    ToFile ? GlLog("%s %i %i\n", Names[10], IntegerValues[0], IntegerValues[1]) : printf("%s %i %i\n", Names[10], IntegerValues[0], IntegerValues[1]);
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
    int MaxLength = 2048;
    int ActualLength = 0;
    char Log[2048];
    glGetProgramInfoLog (ProgrammeReference, MaxLength, &ActualLength, Log);
    printf ("program info log for GL index %u:\n%s", ProgrammeReference, Log);
    GlLog ("program info log for GL index %u:\n%s", ProgrammeReference, Log);
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

void Debug::GlDebugMessageCallback(GLenum Source, GLenum Type, GLuint Id, GLenum Severity, GLsizei Length, const GLchar *Message, const void *UserParam) {
    int SourceInt = Source - 0x8246;
    int TypeInt = Type - 0x824C;
    int SeverityInt = Severity - 0x9146;
    GlLog("GlDebugError: %s %s id: %u %s length: %i %s userParam: %i\n",
          SourceString[SourceInt],
          TypeString[TypeInt],
          Id,
          SeverityString[SeverityInt],
          Length,
          Message,
          *(int*)UserParam
    );
}

void Debug::Init() {
    glfwSetErrorCallback(&Debug::GlfwErrorCallback);
    if (GLEW_KHR_debug) {
        glDebugMessageCallback(&Debug::GlDebugMessageCallback, nullptr);
    }
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

void Debug::GlfwErrorCallback(int Error, const char *Description) {
    GlLog("GLFW Error (%d): %s", Error, Description);
}
