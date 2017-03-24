#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <OpenGl/OpenGl.h>
#include <Shaders/ShaderBuilder.h>
#include <Misc/FrameRate.h>

int main() {
    OpenGl::GetInstance().InitialiseOpenGl();
    GLFWwindow* Window = OpenGl::GetInstance().GetWindow();

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    float points[] = {
            //0.f, 0.5f, 0.f,
            //0.5f, -0.5f, 0.f,
            //-0.5f, -0.5f, 0.f,
            -0.5f, 0.5f, 0.f,
            0.5f, 0.5f, 0.f,
            -0.5f, -0.5f, 0.f,
            0.5f, 0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            -0.5f, -0.5f, 0.f
    };

    for (int i = 0; i < sizeof(points)/sizeof(points[0]); i++) {
        points[i] = points[i] / 4;
    }

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    GLuint ShaderProgramme = ShaderBuilder::CreateProgrammeFromFiles("test", "test");
    GLuint ShaderProgramme2 = ShaderBuilder::CreateProgrammeFromFiles("test", "test2");

    while(!glfwWindowShouldClose(Window)) {
        FrameRate::UpdateFrameCount(Window);
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(ShaderProgramme);
        glBindVertexArray(vao);
        // draw points 0-3 from the currently bound VAO with current in-use shader
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(ShaderProgramme2);
        glDrawArrays(GL_TRIANGLES, 3, 6);

        glfwPollEvents();

        if (GLFW_PRESS == glfwGetKey(Window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(Window, 1);
        }

        glfwSwapBuffers(Window);
    }

    glfwTerminate();
    return 0;
}

