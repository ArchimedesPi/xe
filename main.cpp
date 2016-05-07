#include <iostream>
#include <cstdlib>
#include <cmath>

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <SOIL.h>

#include "gui.h"
#include "scenegraph.h"
#include "gameobject.h"
#include "scene.h"
#include "cube.h"
#include "shaders.h"

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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

    ImGui_ImplGlfwGL3_Init(window, true);

    Scene scene = Scene::Scene();

    scene.rootNode.dumpParameters();

    // populate the scene
    for (int i=0; i<2; i++) {
        Cube *cube = new Cube();
        cube->x = 0;
        cube->y = 0;
        cube->z = 10;
        scene.rootNode.addChild(cube);

        cube->dumpParameters();
        cube->computeBackTransforms();
        cube->dumpTransforms();
    }

    // -- game loop
    while(!glfwWindowShouldClose(window)) {
        int width, height; float ratio;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float)width / (float)height;

        // fix for some weird issues on mac os x
        glViewport(0, 0, width, height);

        // clear the screen
        glClearColor(0.13f, 0.13f, 0.13f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (gui_state.render_wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //renderer.renderAll();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        ImGui_ImplGlfwGL3_NewFrame();
        render_gui();
        ImGui::Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
