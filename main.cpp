#include <iostream>
#include <cstdlib>

#include <imgui.h>
#include <imgui_impl_glfw.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gui.h"

static void glfw_error_callback(int error, const char* description) {
    std::cout << "GLFW error (" << error << "): " << description << '\n';
}

int main(int argc, char* argv[]) {
    GLFWwindow* window;

    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        std::cerr << "could not initialize glfw\n";
        return EXIT_FAILURE;
    }

    window = glfwCreateWindow(640, 480, "[xe][main window]", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "could not create glfw window\n";
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "glewInit() failed\n";
        return -1;
    }

    ImGui_ImplGlfw_Init(window, true);

    while(!glfwWindowShouldClose(window)) {
        // main game loop
        
        int width, height;
        float ratio;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float)width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.0f, 0.0f, 0.0f, 1.0f);

        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();

        ImGui_ImplGlfw_NewFrame();
        {
           // ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_FirstUseEver);
        //ImGui::ShowTestWindow();
        }

        render_gui();

        ImGui::Render();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
