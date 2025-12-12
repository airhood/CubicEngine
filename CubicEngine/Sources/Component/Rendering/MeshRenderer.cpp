#include "MeshRenderer.h"
#include "../Camera.h"
#include "../../Util/RenderUnit.h"
#include "../../Util/Logger.h"
#include "../../Object/GameObject.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <iostream>
#include <format>

using namespace CubicEngine;

static const std::string source = "MeshRenderer.cpp";

MeshRenderer::MeshRenderer() {
	Init();
}

MeshRenderer::~MeshRenderer() {
	
}

void* MeshRenderer::Clone_Obj() const {
	return Clone();
}

Component* MeshRenderer::Clone_Comp() const {
	return Clone();
}

MeshRenderer* MeshRenderer::Clone() const {
	MeshRenderer* meshRenderer = new MeshRenderer();
	meshRenderer->SetMaterial(material);
	meshRenderer->SetMesh(mesh);
	return meshRenderer;
}

void MeshRenderer::Destroy() {

}

void MeshRenderer::Init() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void MeshRenderer::SetMesh(Mesh* mesh) {
	this->mesh = mesh;
	SetupMesh();
}

Mesh* MeshRenderer::GetMesh() const {
	return mesh;
}

void MeshRenderer::SetMaterial(Material* material) {
	this->material = material;
}

Material* MeshRenderer::GetMaterial() const {
	return material;
}

void MeshRenderer::Render(Camera* camera) {
	Logger::Log(LogLevel::TRACE, fmt::format("[Renderer] MeshRenderer render at gameobject '{}'", RootGameObject()->GetName()), source);

	if (material == nullptr) return;
	if (mesh == nullptr) return;

	if (material->mainTexture == nullptr) return;

	glm::mat4 model = RootGameObject()->transform()->GetModelMatrix();
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = camera->GetProjectionMatrix();

	glm::mat4 mvp = projection * view * model;

	for (int pass = 0; pass < ShaderPassCount(material->shader); pass++) {
		UseShader(material->shader, pass);
		//material->PassSetMat4(pass, "u_MVP", mvp);
		material->PassSetMat4(pass, "model", model);
		material->PassSetMat4(pass, "view", view);
		material->PassSetMat4(pass, "projection", projection);

		TextureType textureType = material->mainTexture->GetTextureType();
		switch (material->mainTexture->bindType) {
			case TextureBindType::INDIVIDUAL: {
				material->PassSetBool(pass, "useArray", false);

				GLuint textureID = material->mainTexture->gl_textureID;
				glActiveTexture(GL_TEXTURE0 + static_cast<int>(textureType));
				glBindTexture(GL_TEXTURE_2D, textureID);
				glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

				material->PassSetInt(pass, "texture_diffuse", static_cast<int>(textureType));

				// trash value
				material->PassSetInt(pass, "textureArray", static_cast<int>(textureType));
				material->PassSetFloat(pass, "layerIndex", 0);
				material->PassSetVec4(pass, "subUV", glm::vec4(0, 0, 1, 1));

				break;
			}
			case TextureBindType::ATLAS: {
				material->PassSetBool(pass, "useArray", true);

				GLuint texture2DArrayID = material->mainTexture->textureArray->textureArrayID;
				glActiveTexture(GL_TEXTURE0 + static_cast<int>(textureType));
				glBindTexture(GL_TEXTURE_2D, 0);
				glBindTexture(GL_TEXTURE_2D_ARRAY, texture2DArrayID);

				// trash value
				material->PassSetInt(pass, "texture_diffuse", static_cast<int>(textureType));

				material->PassSetInt(pass, "textureArray", static_cast<int>(textureType));
				material->PassSetFloat(pass, "layerIndex", material->mainTexture->layerIndex);
				material->PassSetVec4(pass, "subUV", glm::vec4(0, 0, 1, 1));

				break;
			}
			default:
				Logger::Log(LogLevel::ERROR, std::format("[TextureManager] Invalid TextureBindType {}", static_cast<int>(material->mainTexture->bindType)), source);
				return;
		}

		material->Apply(pass, CubicEngine::RenderUnit::ALBEDO);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glUseProgram(0);
	}
}

void MeshRenderer::UpdateMesh() const {
	mesh->CalculateNormal();
	mesh->CalculateTangent();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex), mesh->vertices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(uint32_t), mesh->indices.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}

void MeshRenderer::SetupMesh() {
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex), mesh->vertices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(uint32_t), mesh->indices.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
	glEnableVertexAttribArray(4);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
