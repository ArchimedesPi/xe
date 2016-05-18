#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <functional>
#include <random>

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <SOIL.h>

#include "game.h"
#include "gui.h"
#include "scenegraph.h"
#include "gameobject.h"
#include "scene.h"
#include "renderer.h"
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

    Game game = Game();

    Camera camera = Camera();
    camera.lookAt(glm::vec3(0, 0, 0));
    camera.setEye(glm::vec3(0, 0, -20));

    Renderer renderer = Renderer(&game, &camera);
    CubeRenderer *cubeRenderer = new CubeRenderer();
    renderer.addRenderable(cubeRenderer);
    renderer.setupRenderables();

    Scene scene = Scene();
    //scene.rootNode.dumpParameters();

    // populate the scene
    for (int i=0; i<10; i++) {
        Cube *cube = new Cube();
        cube->setPosition(i*0.5, 0, i*0.5);
        cube->n.pitch = 0.1*i;
        scene.addObject(cube);
        scene.rootNode.addChild(&cube->n);
    
        cube->n.computeBackTransforms();
        //cube->n.dumpParameters();
        //cube->n.dumpTransforms();
    }


    // -- game loop
    while(!glfwWindowShouldClose(window)) {
        scene.rootNode.computeDependantTransforms();

        
        GLfloat radius = 10.0f;
        GLfloat camX = sin(glfwGetTime()) * radius;
        GLfloat camZ = cos(glfwGetTime()) * radius;
        camera.setEye(glm::vec3(camX, 0, camZ));

        glfwGetFramebufferSize(window, &game.width, &game.height);
        game.ratio = (float)game.width / (float)game.height;

        // fix for some weird issues on mac os x
        glViewport(0, 0, game.width, game.height);

        // clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (gui_state.render_wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for (int i=0; i<scene.rootNode.children.size(); i++) {
            renderer.render(cubeRenderer, scene.objects.at(i));
        }
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
