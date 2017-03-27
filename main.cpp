#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <OpenGl/OpenGl.h>
#include "Shaders/ShaderBuilder.h"
#include <Misc/FrameRate.h>

int main() {
    OpenGl::GetInstance().InitialiseOpenGl();
    GLFWwindow* Window = OpenGl::GetInstance().GetWindow();

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    GLfloat points[] = {
        -0.5f, 0.5f, 0.f,
        0.5f, 0.5f, 0.f,
        -0.5f, -0.5f, 0.f,
    };

    GLfloat colours[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    float matrix[] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };


    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint ColourVertexBufferObject = 0;
    glGenBuffers(1, &ColourVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, ColourVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, ColourVertexBufferObject);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    GLuint ShaderProgramme = ShaderBuilder::CreateProgrammeFromFiles("color-map", "assigned-colour");
    int MatrixLocation = glGetUniformLocation (ShaderProgramme, "Matrix3");
    //GLuint ShaderProgramme2 = ShaderBuilder::CreateProgrammeFromFiles("test", "test2");

    while(!glfwWindowShouldClose(Window)) {
        FrameRate::UpdateFrameCount(Window);
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(ShaderProgramme);
        glUniformMatrix4fv (MatrixLocation, 1, GL_FALSE, matrix);
        glBindVertexArray(vao);
        // draw points 0-3 from the currently bound VAO with current in-use shader
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //glUseProgram(ShaderProgramme2);
        //glDrawArrays(GL_TRIANGLES, 3, 6);

        glfwPollEvents();

        if (GLFW_PRESS == glfwGetKey(Window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(Window, 1);
        }

        if (GLFW_PRESS == glfwGetKey(Window, GLFW_KEY_RIGHT)) {
            matrix[3] += 0.01;
//            matrix[12] += 0.01;
        }

        glfwSwapBuffers(Window);
    }

    glfwTerminate();
    return 0;
}

