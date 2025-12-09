#include "Material.h"

using namespace CubicEngine;

Material::Material() {
	shaderProgram = glCreateProgram();
}

void Material::Destroy() {

}

void* Material::Clone_Obj() const {
	return Clone();
}

Material* Material::Clone() const {
	Material* material = new Material();
	material->shader = shader;
	return material;
}

void Material::SetBool(const std::string& name, bool value) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetBool(pass, name, value);
	}
}

void Material::SetInt(const std::string& name, int value) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetInt(pass, name, value);
	}
}

void Material::SetFloat(const std::string& name, float value) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetFloat(pass, name, value);
	}
}

void Material::SetVec2(const std::string& name, const glm::vec2& value) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec2(pass, name, value);
	}
}

void Material::SetVec2(const std::string& name, float x, float y) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec2(pass, name, x, y);
	}
}

void Material::SetVec3(const std::string& name, const glm::vec3& value) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec2(pass, name, value);
	}
}

void Material::SetVec3(const std::string& name, float x, float y, float z) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec3(pass, name, x, y, z);
	}
}

void Material::SetVec4(const std::string& name, const glm::vec4& value) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec4(pass, name, value);
	}
}

void Material::SetVec4(const std::string& name, float x, float y, float z, float w) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec4(pass, name, x, y, z, w);
	}
}

void Material::SetMat2(const std::string& name, const glm::mat2& mat) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetMat2(pass, name, mat);
	}
}

void Material::SetMat3(const std::string& name, const glm::mat3& mat) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetMat3(pass, name, mat);
	}
}

void Material::SetMat4(const std::string& name, const glm::mat4& mat) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetMat4(pass, name, mat);
	}
}

void Material::PassSetBool(int pass, const std::string& name, bool value) {
	uniform_buffer[pass].bools[name] = value;
}

void Material::PassSetInt(int pass, const std::string& name, int value) {
	uniform_buffer[pass].ints[name] = value;
}

void Material::PassSetFloat(int pass, const std::string& name, float value) {
	uniform_buffer[pass].floats[name] = value;
}

void Material::PassSetVec2(int pass, const std::string& name, const glm::vec2& value) {
	uniform_buffer[pass].vec2s[name] = value;
}

void Material::PassSetVec2(int pass, const std::string& name, float x, float y) {
	uniform_buffer[pass].vec2s[name] = glm::vec2(x, y);
}

void Material::PassSetVec3(int pass, const std::string& name, const glm::vec3& value) {
	uniform_buffer[pass].vec3s[name] = value;
}

void Material::PassSetVec3(int pass, const std::string& name, float x, float y, float z) {
	uniform_buffer[pass].vec3s[name] = glm::vec3(x, y, z);
}

void Material::PassSetVec4(int pass, const std::string& name, const glm::vec4& value) {
	uniform_buffer[pass].vec4s[name] = value;
}

void Material::PassSetVec4(int pass, const std::string& name, float x, float y, float z, float w) {
	uniform_buffer[pass].vec4s[name] = glm::vec4(x, y, z, w);
}

void Material::PassSetMat2(int pass, const std::string& name, const glm::mat2& mat) {
	uniform_buffer[pass].mat2s[name] = mat;
}

void Material::PassSetMat3(int pass, const std::string& name, const glm::mat3& mat) {
	uniform_buffer[pass].mat3s[name] = mat;
}

void Material::PassSetMat4(int pass, const std::string& name, const glm::mat4& mat) {
	uniform_buffer[pass].mat4s[name] = mat;
}

void Material::Apply() {
	for (auto& pass_uniform : uniform_buffer) {
		int pass = pass_uniform.first;
		for (auto& bool_ : pass_uniform.second.bools) {
			std::string name = bool_.first;
			auto value = bool_.second;
			glUniform1i(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), (int)value);
		}

		for (auto& int_ : pass_uniform.second.ints) {
			std::string name = int_.first;
			auto value = int_.second;
			glUniform1i(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), value);
		}

		for (auto& float_ : pass_uniform.second.floats) {
			std::string name = float_.first;
			auto value = float_.second;
			glUniform1f(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), value);
		}

		for (auto& vec2 : pass_uniform.second.vec2s) {
			std::string name = vec2.first;
			auto value = vec2.second;
			glUniform2fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, &value[0]);
		}

		for (auto& vec3 : pass_uniform.second.vec3s) {
			std::string name = vec3.first;
			auto value = vec3.second;
			glUniform3fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, &value[0]);
		}

		for (auto& vec4 : pass_uniform.second.vec4s) {
			std::string name = vec4.first;
			auto value = vec4.second;
			glUniform4fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, &value[0]);
		}

		for (auto& mat2 : pass_uniform.second.mat2s) {
			std::string name = mat2.first;
			auto mat = mat2.second;
			glUniformMatrix2fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}

		for (auto& mat3 : pass_uniform.second.mat3s) {
			std::string name = mat3.first;
			auto mat = mat3.second;
			glUniformMatrix3fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}

		for (auto& mat4 : pass_uniform.second.mat4s) {
			std::string name = mat4.first;
			auto mat = mat4.second;
			glUniformMatrix4fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
	}
}