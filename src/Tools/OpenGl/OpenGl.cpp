//
// Created by Jury Verrigni on 3/24/17.
//

#include <Misc/Debug.h>
#include "OpenGl.h"

bool OpenGl::InitialiseOpenGl() {
    if (Initialised) {
        return true;
    }

    Debug::GlLog ("starting GLFW %s\n", glfwGetVersionString ());

    glfwSetErrorCallback (&OpenGl::GlfwErrorCallback);
    if (!glfwInit ()) {
        Debug::GlLog ("ERROR: could not start GLFW3\n");
        return false;
    }

    // uncomment these lines if on Apple OS X
    glfwWindowHint (GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_SAMPLES, 4);

//	GLFWmonitor* mon = glfwGetPrimaryMonitor ();
//	const GLFWvidmode* vmode = glfwGetVideoMode (mon);
//	Window = glfwCreateWindow (
//		vmode->width, vmode->height, "Extended GL Init", mon, NULL
//	);

    Window = glfwCreateWindow (
            WindowWidth, WindowHeight, "Extended Init.", NULL, NULL
    );
    if (!Window) {
        Debug::GlLog ("ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return false;
    }
    glfwSetWindowSizeCallback (Window, &OpenGl::GlfwWindowSizeCallback);
    glfwMakeContextCurrent (Window);

    glewExperimental = GL_TRUE;
    glewInit ();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable (GL_CULL_FACE);
    glCullFace (GL_BACK);
    glFrontFace (GL_CW);

    Debug::PrintGlLog(true);

    Initialised = true;

    return true;
}


void OpenGl::GlfwErrorCallback(int Error, const char *Description) {
    Debug::GlLog ("GLFW Error (#%d): %s", Error, Description);
}

void OpenGl::GlfwWindowSizeCallback(GLFWwindow *Window, int Width, int Height) {
    OpenGl::GetInstance().WindowWidth = Width;
    OpenGl::GetInstance().WindowHeight = Height;
    Debug::GlLog ("Width %i Height %i\n", Width, Height);
    /* update any perspective matrices used here */
}

GLFWwindow *OpenGl::GetWindow() {
    return Window;
}
