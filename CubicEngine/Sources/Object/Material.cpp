#include "Material.h"

using namespace CubicEngine;

void Material::SetBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(shader->ID, name.c_str()), (int)value);
}

void Material::SetInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(shader->ID, name.c_str()), value);
}

void Material::SetFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(shader->ID, name.c_str()), value);
}

void Material::SetVec2(const std::string& name, const glm::vec2& value) const {
	glUniform2fv(glGetUniformLocation(shader->ID, name.c_str()), 1, &value[0]);
}

void Material::SetVec2(const std::string& name, float x, float y) const {
	glUniform2f(glGetUniformLocation(shader->ID, name.c_str()), x, y);
}

void Material::SetVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(shader->ID, name.c_str()), 1, &value[0]);
}

void Material::SetVec3(const std::string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(shader->ID, name.c_str()), x, y, z);
}

void Material::SetVec4(const std::string& name, const glm::vec4& value) const {
	glUniform4fv(glGetUniformLocation(shader->ID, name.c_str()), 1, &value[0]);
}

void Material::SetVec4(const std::string& name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(shader->ID, name.c_str()), x, y, z, w);
}

void Material::SetMat2(const std::string& name, const glm::mat2& mat) const {
	glUniformMatrix2fv(glGetUniformLocation(shader->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Material::SetMat3(const std::string& name, const glm::mat3& mat) const {
	glUniformMatrix3fv(glGetUniformLocation(shader->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Material::SetMat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}