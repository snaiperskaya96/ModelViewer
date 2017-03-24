//
// Created by Jury Verrigni on 3/24/17.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "FrameRate.h"

void FrameRate::UpdateFrameCount(GLFWwindow* Window) {
    static double PreviousTime = glfwGetTime();
    static int FrameCount;
    double CurrentSeconds = glfwGetTime();
    double ElpasedSeconds = CurrentSeconds - PreviousTime;
    if (ElpasedSeconds > 0.1) {
        PreviousTime = CurrentSeconds;
        double fps = (double)FrameCount / ElpasedSeconds;
        char tmp[128];
        sprintf(tmp, "opengl @ fps: %.2f", fps);
        glfwSetWindowTitle(Window, tmp);
        FrameCount = 0;
    }
    FrameCount++;
}
