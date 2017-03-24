//
// Created by Jury Verrigni on 3/24/17.
//

#ifndef MODELVIEWER_OPENGL_H
#define MODELVIEWER_OPENGL_H


#include <GLFW/glfw3.h>

class OpenGl {
public:
    static OpenGl& GetInstance()
    {
        static OpenGl instance;
        return instance;
    }
    bool InitialiseOpenGl();
    GLFWwindow* GetWindow();
public:
    static void GlfwErrorCallback(int Error, const char *Description);
    static void GlfwWindowSizeCallback(GLFWwindow *Window, int Width, int Height);
private:
    OpenGl() {}
    GLFWwindow *Window;
    int WindowWidth = 800;
    int WindowHeight = 480;
    bool Initialised;
public:
    // C++11
    OpenGl(OpenGl const&) = delete;
    void operator=(OpenGl const&) = delete;



};


#endif //MODELVIEWER_OPENGL_H
