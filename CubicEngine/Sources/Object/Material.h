#pragma once

#include "Object.h"
#include "Shader.h"

namespace CubicEngine {
	class Material : public Object {
	public:
		Material();

		void Destroy() override;

		void* Clone_Obj() const override;

		Material* Clone() const;

		Shader* shader;

		void SetBool(const std::string& name, bool value) const;

		void SetInt(const std::string& name, int value) const;

		void SetFloat(const std::string& name, float value) const;

		void SetVec2(const std::string& name, const glm::vec2& value) const;

		void SetVec2(const std::string& name, float x, float y) const;

		void SetVec3(const std::string& name, const glm::vec3& value) const;

		void SetVec3(const std::string& name, float x, float y, float z) const;

		void SetVec4(const std::string& name, const glm::vec4& value) const;

		void SetVec4(const std::string& name, float x, float y, float z, float w) const;

		void SetMat2(const std::string& name, const glm::mat2& mat) const;

		void SetMat3(const std::string& name, const glm::mat3& mat) const;

		void SetMat4(const std::string& name, const glm::mat4& mat) const;


		void PassSetBool(int pass, const std::string& name, bool value) const;

		void PassSetInt(int pass, const std::string& name, int value) const;

		void PassSetFloat(int pass, const std::string& name, float value) const;

		void PassSetVec2(int pass, const std::string& name, const glm::vec2& value) const;

		void PassSetVec2(int pass, const std::string& name, float x, float y) const;

		void PassSetVec3(int pass, const std::string& name, const glm::vec3& value) const;

		void PassSetVec3(int pass, const std::string& name, float x, float y, float z) const;

		void PassSetVec4(int pass, const std::string& name, const glm::vec4& value) const;

		void PassSetVec4(int pass, const std::string& name, float x, float y, float z, float w) const;

		void PassSetMat2(int pass, const std::string& name, const glm::mat2& mat) const;

		void PassSetMat3(int pass, const std::string& name, const glm::mat3& mat) const;

		void PassSetMat4(int pass, const std::string& name, const glm::mat4& mat) const;

	private:
		GLuint shaderProgram = 0;
	};
}