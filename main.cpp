#include <ModelViewer.h>
#include <Misc/FrameRate.h>
#include <Actors/Actor.h>
#include <Actors/TestActor.h>
#include <Misc/Debug.h>
#include <Tools/Shaders/ShaderBuilder.h>

int main() {
    OpenGl::GetInstance().InitialiseOpenGl();
    Debug::Init();
    GLFWwindow* Window = OpenGl::GetInstance().GetWindow();

    TestActor* actor = new TestActor();

    actor->Init();

    while(!glfwWindowShouldClose(Window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor( 0.3, 0, 0.7, 1);
        FrameRate::UpdateFrameCount(Window);

        actor->Update();

        glfwPollEvents();

        if (GLFW_PRESS == glfwGetKey(Window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(Window, 1);
        }

        glfwSwapBuffers(Window);
    }

    delete actor;
    glfwTerminate();
    return 0;
}

