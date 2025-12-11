#include "Renderer2D.h"
#include "../../Object/Sprite.h"
#include "../Camera.h"
#include "../../Util/RenderUnit.h"
#include "../../Util/Logger.h"
#include "../../Object/GameObject.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>

using namespace CubicEngine;

static const std::string source = "Renderer2D.cpp";

Renderer2D::Renderer2D() {
    Init();
}

Renderer2D::~Renderer2D() {

}

void* Renderer2D::Clone_Obj() const {
    return Clone();
}

Component* Renderer2D::Clone_Comp() const {
    return Clone();
}

Renderer2D* Renderer2D::Clone() const {
    Renderer2D* renderer2D = new Renderer2D();
    renderer2D->sprite = sprite;
    renderer2D->material = material;

    return renderer2D;
}

void Renderer2D::Destroy() {

}

void Renderer2D::Init() {
    sprite = Sprite();

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
    Logger::Log(LogLevel::TRACE, fmt::format("[Renderer] Renderer2d render at gameobject '{}'", RootGameObject()->GetName()), source);
    
    if (material == nullptr) return;
    if (sprite.texture == nullptr) return;
    
    glm::vec3 position = Component::RootGameObject()->transform()->position;
    glm::vec2 offset = glm::vec2(0.0f, 0.0f);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x - offset.x, position.y - offset.y, position.z));
    model = glm::scale(model, glm::vec3(sprite.texture->width(), sprite.texture->height(), 1.0f));

    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = camera->GetProjectionMatrix();

    glm::mat4 mvp = projection * view * model;

    for (int pass = 0; pass < ShaderPassCount(material->shader); pass++) {
        UseShader(material->shader, pass);
        //material->PassSetMat4(pass, "u_MVP", mvp);
        material->PassSetMat4(pass, "model", model);
        material->PassSetMat4(pass, "view", view);
        material->PassSetMat4(pass, "projection", projection);

        material->PassSetInt(pass, "texture_diffuse1", CubicEngine::RenderUnit::SPRITE);

        material->Apply(pass, CubicEngine::RenderUnit::SPRITE);

        sprite.texture->Bind(CubicEngine::RenderUnit::SPRITE);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glUseProgram(0);
    }
}

void Renderer2D::SetMaterial(Material* material) {
    this->material = material;
}

Material* Renderer2D::GetMaterial() const {
    return material;
}

void Renderer2D::SetSprite(Sprite sprite) {
    this->sprite = sprite;
    UpdateBuffers();
}

Sprite Renderer2D::GetSprite() const {
    return this->sprite;
}

void Renderer2D::UpdateBuffers() {
    if (sprite.texture == nullptr) return;

    float worldWidth = (float)(sprite.texture->width()) / (float)(sprite.pixelsPerUnit);
    float worldHeight = (float)(sprite.texture->height()) / (float)(sprite.pixelsPerUnit);

    float unitPerPixel = 1.0f / (float)(sprite.pixelsPerUnit);

    float offsetX = unitPerPixel * ((float)(sprite.pivot.x) / (float)(sprite.texture->width()));
    float offsetY = unitPerPixel * ((float)(sprite.pivot.y) / (float)(sprite.texture->height()));

    float vertices[] = {
        // x, y, z, u, v
        -unitPerPixel / 2.0f - offsetX,   -unitPerPixel / 2.0f - offsetY,   0.0f,   0.0f,   0.0f,
         unitPerPixel / 2.0f - offsetX,   -unitPerPixel / 2.0f - offsetY,   0.0f,   1.0f,   0.0f,
         unitPerPixel / 2.0f - offsetX,    unitPerPixel / 2.0f - offsetY,   0.0f,   1.0f,   1.0f,
        -unitPerPixel / 2.0f - offsetX,    unitPerPixel / 2.0f - offsetY,   0.0f,   0.0f,   1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // tex coords
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
