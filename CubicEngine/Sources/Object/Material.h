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
	};

	class Material : public Object {
	public:
		Material();

		void Destroy() override;

		void* Clone_Obj() const override;

		Material* Clone() const;

		Shader* shader;

		void SetBool(const std::string& name, bool value);

		void SetInt(const std::string& name, int value);

		void SetFloat(const std::string& name, float value);

		void SetVec2(const std::string& name, const glm::vec2& value);

		void SetVec2(const std::string& name, float x, float y);

		void SetVec3(const std::string& name, const glm::vec3& value);

		void SetVec3(const std::string& name, float x, float y, float z);

		void SetVec4(const std::string& name, const glm::vec4& value);

		void SetVec4(const std::string& name, float x, float y, float z, float w);

		void SetMat2(const std::string& name, const glm::mat2& mat);

		void SetMat3(const std::string& name, const glm::mat3& mat);

		void SetMat4(const std::string& name, const glm::mat4& mat);


		void PassSetBool(int pass, const std::string& name, bool value);

		void PassSetInt(int pass, const std::string& name, int value);

		void PassSetFloat(int pass, const std::string& name, float value);

		void PassSetVec2(int pass, const std::string& name, const glm::vec2& value);

		void PassSetVec2(int pass, const std::string& name, float x, float y);

		void PassSetVec3(int pass, const std::string& name, const glm::vec3& value);

		void PassSetVec3(int pass, const std::string& name, float x, float y, float z);

		void PassSetVec4(int pass, const std::string& name, const glm::vec4& value);

		void PassSetVec4(int pass, const std::string& name, float x, float y, float z, float w);

		void PassSetMat2(int pass, const std::string& name, const glm::mat2& mat);

		void PassSetMat3(int pass, const std::string& name, const glm::mat3& mat);

		void PassSetMat4(int pass, const std::string& name, const glm::mat4& mat);

	private:
		GLuint shaderProgram = 0;

		std::unordered_map<int, PassUniforms> uniform_buffer;

		friend class RenderManager;
		void Apply();
	};
}