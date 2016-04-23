#include <iostream>
#include <cstdlib>

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gui.h"
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

    GLuint vertexShader = load_shader_from_file("shaders/vertex/passthrough.vert", GL_VERTEX_SHADER);
    GLuint fragmentShader = load_shader_from_file("shaders/fragment/helloworld.frag", GL_FRAGMENT_SHADER);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    link_shader_program(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLfloat vertices[] = {
        -0.6f, -0.4f, 0.0f,
        0.6f, -0.4f, 0.0f,
        0.0f, 0.6f, 0.0f,
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // unbind buffer, vertex array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(window)) {
        // main game loop
        
        int width, height;
        float ratio;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float)width / (float)height;

        glViewport(0, 0, width, height);

        glClearColor(0.13f, 0.13f, 0.13f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

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
