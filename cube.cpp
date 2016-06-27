#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "cube.h"

constexpr GLfloat CubeRenderer::vertices[];

void CubeRenderer::setup() {
    ShaderFile vertexShader = ShaderFile::fromFile("shaders/vertex/pmat_normals.vert", GL_VERTEX_SHADER);
    ShaderFile fragmentShader = ShaderFile::fromFile("shaders/fragment/flatcolor.frag", GL_FRAGMENT_SHADER);
 
    shader = Shader()
        .addShaderFile(vertexShader)
        .addShaderFile(fragmentShader)
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
    glm::mat3 normalmat;
   
    model = obj->n.world_matrix;

    view = camera->lookMatrix();
    projection = glm::perspective(45.0f, game->ratio, 0.1f, 100.0f);

    normalmat = glm::inverseTranspose(glm::mat3(model));

    glUniformMatrix4fv(shader.uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(shader.uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader.uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix3fv(shader.uniform("normalmat"), 1, GL_FALSE, glm::value_ptr(normalmat));

    glUniform4f(shader.uniform("color_"), 1.0f, 0.5f, 0.2f, 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
