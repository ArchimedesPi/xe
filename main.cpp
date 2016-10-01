#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <functional>
#include <random>
#include <memory>

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <sol.hpp>

#include <filesystem/path.h>

#include "game.h"
#include "gui.h"
#include "ui/logwindow.h"
#include "scenegraph.h"
#include "gameobject.h"
#include "scene.h"
#include "renderer.h"
#include "cube.h"
#include "shaders.h"

#include "services/locator.h"
#include "services/input.h"
#include "services/resources.h"


static void glfw_error_callback(int error, const char* description) {
    std::cout << "GLFW error (" << error << "): " << description << '\n';
}

int main(int argc, char* argv[]) {
    // -- Set up a GLFW window
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


    // -- Set up UI, game, camera, etc
    services::Locator::initialize();
    auto input = new services::DesktopInput();
    auto resource_locator = new services::FilesystemResourceLocator();
    resource_locator->basedir = services::FilesystemResourceLocator::backtrackToBasedir(filesystem::path::getcwd());
    services::Locator::provideInput(input);
    services::Locator::provideResourceLocator(resource_locator);

    // init + config gui
    ImGui_ImplGlfwGL3_Init(window, true);
    setup_gui();


    // enumerate controllers
    input->updateControllers();

    Game game = Game();

    Camera camera = Camera();
    camera.lookAt(glm::vec3(0.75f, 0.75f, 0.75f));
    camera.setEye(glm::vec3(5, 5, 5));

    Renderer renderer = Renderer(&game, &camera);
    CubeRenderer *cubeRenderer = new CubeRenderer();
    renderer.addRenderable(cubeRenderer);
    renderer.setupRenderables();

    Scene scene = Scene();

    // populate the scene with test cube(s)
    for (int i=0; i<1; i++) {
        for (int j=0; j<1; j++) {
            for (int k=0; k<1; k++) {
                Cube *cube = new Cube();
                cube->setPosition(i*1.5, j*1.5, k*1.5);
                scene.addObject(cube);
                scene.rootNode.addChild(&cube->n);
    
                cube->n.computeBackTransforms();
            }
        }
    }

    // enable gl depth testing (occlusion should be a thing)
    glEnable(GL_DEPTH_TEST);

    // -- game loop
    while(!glfwWindowShouldClose(window)) {
        ImGui_ImplGlfwGL3_NewFrame();

        camera.setEye(glm::vec3(sin(glfwGetTime()) * 5.0f,
                    5.0f,
                    cos(glfwGetTime()) * 5.0f));

        for (int i=0; i<scene.objects.size(); i++) {
            scene.objects.at(i)->n.yaw = 2 * glfwGetTime();
            scene.objects.at(i)->n.roll = 1 * glfwGetTime();
        }
        scene.rootNode.computeDependantTransforms();

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

        render_gui();
        ImGui::Render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        std::cout << std::flush;
        std::cerr << std::flush;
    }

//     // When the gameloop exits, cleanly shut everything down
//     ImGui_ImplGlfwGL3_Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
