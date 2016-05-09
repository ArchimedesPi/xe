#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "cube.h"

constexpr GLfloat CubeRenderer::vertices[];

void CubeRenderer::setup() {
    Shader vertexShader = Shader::fromFile("shaders/vertex/project_matrix.vert", GL_VERTEX_SHADER);
    Shader fragmentShader = Shader::fromFile("shaders/fragment/flatcolor.frag", GL_FRAGMENT_SHADER);
 
    shader = ShaderProgram::ShaderProgram()
        .addShader(vertexShader)
        .addShader(fragmentShader)
        .link();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void CubeRenderer::renderInstance(GameObject *obj, Game *game_) {
    shader.use();

    glm::mat4 model, view, projection;
   
    model = obj->world_matrix;

    // "camera" shit
    view = glm::translate(view, glm::vec3(0.0f, 1.1f, -3.0f));
    projection = glm::perspective(45.0f, 1.5f, 0.1f, 100.0f);


    glUniformMatrix4fv(shader.uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(shader.uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader.uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform4f(shader.uniform("color_"), 1.0f, 0.5f, 0.2f, 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
