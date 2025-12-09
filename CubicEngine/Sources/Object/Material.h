#pragma once

#include "Object.h"
#include "Shader.h"
#include <unordered_map>
#include "Texture.h"

namespace CubicEngine {
	struct PassUniforms {
		std::unordered_map<std::string, int> bools;
		std::unordered_map<std::string, int> ints;
		std::unordered_map<std::string, float> floats;
		std::unordered_map<std::string, glm::vec2> vec2s;
		std::unordered_map<std::string, glm::vec3> vec3s;
		std::unordered_map<std::string, glm::vec4> vec4s;
		std::unordered_map<std::string, glm::mat2> mat2s;
		std::unordered_map<std::string, glm::mat3> mat3s;
		std::unordered_map<std::string, glm::mat4> mat4s;
		std::unordered_map<std::string, const Texture*> textures;
	};

	class Material : public Object {
	public:
		Material();

		void Destroy() override;

		void* Clone_Obj() const override;

		Material* Clone() const;

		Shader* shader;

		Texture* mainTexture;
		glm::vec2 mainTextureOffset;
		glm::vec2 mainTextureScale;

		void SetBool(const std::string& name, bool val);

		void SetInt(const std::string& name, int val);

		void SetFloat(const std::string& name, float val);

		void SetVec2(const std::string& name, const glm::vec2& val);

		void SetVec2(const std::string& name, float x, float y);

		void SetVec3(const std::string& name, const glm::vec3& val);

		void SetVec3(const std::string& name, float x, float y, float z);

		void SetVec4(const std::string& name, const glm::vec4& val);

		void SetVec4(const std::string& name, float x, float y, float z, float w);

		void SetMat2(const std::string& name, const glm::mat2& mat);

		void SetMat3(const std::string& name, const glm::mat3& mat);

		void SetMat4(const std::string& name, const glm::mat4& mat);

		void SetTexture(const std::string& name, const Texture* tex);


		void PassSetBool(int pass, const std::string& name, bool val);

		void PassSetInt(int pass, const std::string& name, int val);

		void PassSetFloat(int pass, const std::string& name, float val);

		void PassSetVec2(int pass, const std::string& name, const glm::vec2& val);

		void PassSetVec2(int pass, const std::string& name, float x, float y);

		void PassSetVec3(int pass, const std::string& name, const glm::vec3& val);

		void PassSetVec3(int pass, const std::string& name, float x, float y, float z);

		void PassSetVec4(int pass, const std::string& name, const glm::vec4& val);

		void PassSetVec4(int pass, const std::string& name, float x, float y, float z, float w);

		void PassSetMat2(int pass, const std::string& name, const glm::mat2& mat);

		void PassSetMat3(int pass, const std::string& name, const glm::mat3& mat);

		void PassSetMat4(int pass, const std::string& name, const glm::mat4& mat);

		void PassSetTexture(int pass, const std::string& name, const Texture* tex);

	private:
		GLuint shaderProgram = 0;

		std::unordered_map<int, PassUniforms> uniform_buffer;

		friend class RenderManager;
		friend class Renderer;
		friend class Renderer2D;
		friend class MeshRenderer;
		void Apply(int pass, int unit);
	};
}