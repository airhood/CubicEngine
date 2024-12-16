#include "Renderer2D.h"
#include "../Object/Sprite.h"

using namespace CubicEngine;

Renderer2D::~Renderer2D() {

}

void Renderer2D::Destroy() {

}

void Renderer2D::Init() {
    float vertices[] = {
        // x, y, z, u, v
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // tex coords
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer2D::Render(Camera* camera) {
    glm::vec3 position = RootGameObject()->transform()->position;
    glm::vec2 offset = glm::vec2(
        sprite->pivot.x * sprite->texture->width(),
        sprite->pivot.y * sprite->texture->height());

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x - offset.x, position.y - offset.y, position.z));
    model = glm::scale(model, glm::vec3(sprite->texture->width(), sprite->texture->height(), 1.0f));

    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = camera->GetProjectionMatrix();

    for (int i = 0; i < ShaderPassCount(material->shader); i++) {
        UseShader(material->shader, i);
        //material->PassSetMat4(i, "u_MVP", mvp);
        material->PassSetMat4(i, "model", model);
        material->PassSetMat4(i, "view", view);
        material->PassSetMat4(i, "projection", projection);
        BindTexture(GL_TEXTURE_2D, sprite->texture);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void Renderer2D::SetMaterial(Material* material) {
    this->material = material;
}

Material* Renderer2D::GetMaterial() const {
    return material;
}