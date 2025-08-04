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

void Material::SetBool(const std::string& name, bool value) const {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetBool(pass, name, value);
	}
}

void Material::SetInt(const std::string& name, int value) const {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetInt(pass, name, value);
	}
}

void Material::SetFloat(const std::string& name, float value) const {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetFloat(pass, name, value);
	}
}

void Material::SetVec2(const std::string& name, const glm::vec2& value) const {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec2(pass, name, value);
	}
}

void Material::SetVec2(const std::string& name, float x, float y) const {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec2(pass, name, x, y);
	}
}

void Material::SetVec3(const std::string& name, const glm::vec3& value) const {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec2(pass, name, value);
	}
}

void Material::SetVec3(const std::string& name, float x, float y, float z) const {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec3(pass, name, x, y, z);
	}
}

void Material::SetVec4(const std::string& name, const glm::vec4& value) const {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec4(pass, name, value);
	}
}

void Material::SetVec4(const std::string& name, float x, float y, float z, float w) const {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec4(pass, name, x, y, z, w);
	}
}

void Material::SetMat2(const std::string& name, const glm::mat2& mat) const {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetMat2(pass, name, mat);
	}
}

void Material::SetMat3(const std::string& name, const glm::mat3& mat) const {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetMat3(pass, name, mat);
	}
}

void Material::SetMat4(const std::string& name, const glm::mat4& mat) const {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetMat4(pass, name, mat);
	}
}

void Material::PassSetBool(int pass, const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), (int)value);
}

void Material::PassSetInt(int pass, const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), value);
}

void Material::PassSetFloat(int pass, const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), value);
}

void Material::PassSetVec2(int pass, const std::string& name, const glm::vec2& value) const {
	glUniform2fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, &value[0]);
}

void Material::PassSetVec2(int pass, const std::string& name, float x, float y) const {
	glUniform2f(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), x, y);
}

void Material::PassSetVec3(int pass, const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, &value[0]);
}

void Material::PassSetVec3(int pass, const std::string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), x, y, z);
}

void Material::PassSetVec4(int pass, const std::string& name, const glm::vec4& value) const {
	glUniform4fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, &value[0]);
}

void Material::PassSetVec4(int pass, const std::string& name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), x, y, z, w);
}

void Material::PassSetMat2(int pass, const std::string& name, const glm::mat2& mat) const {
	glUniformMatrix2fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Material::PassSetMat3(int pass, const std::string& name, const glm::mat3& mat) const {
	glUniformMatrix3fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Material::PassSetMat4(int pass, const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}