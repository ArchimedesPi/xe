#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "cube.h"

constexpr GLfloat CubeRenderer::vertices[];

void CubeRenderer::setup() {
    Shader vertexShader = Shader::fromFile("shaders/vertex/pmat_normals.vert", GL_VERTEX_SHADER);
    Shader fragmentShader = Shader::fromFile("shaders/fragment/simplelighting.frag", GL_FRAGMENT_SHADER);
 
    shader = ShaderProgram()
        .addShader(vertexShader)
        .addShader(fragmentShader)
        .link();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void CubeRenderer::renderInstance(GameObject *obj, Game *game, Camera *camera) {
    shader.use();

    glm::mat4 model, view, projection;
   
    model = obj->n.world_matrix;

    view = camera->lookMatrix();
    projection = glm::perspective(45.0f, game->ratio, 0.1f, 100.0f);

    glUniformMatrix4fv(shader.uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(shader.uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader.uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform4f(shader.uniform("object_color"), 1.0f, 0.5f, 0.2f, 1.0f);
    glUniform3f(shader.uniform("light_color"), 1.0f, 1.0f, 1.0f);
    glUniform3f(shader.uniform("light_position"), camera->eye.x, camera->eye.y, camera->eye.z);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
