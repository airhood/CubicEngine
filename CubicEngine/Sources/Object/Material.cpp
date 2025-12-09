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

void Material::SetBool(const std::string& name, bool val) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetBool(pass, name, val);
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

void Material::SetVec3(const std::string& name, const glm::vec3& val) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec2(pass, name, val);
	}
}

void Material::SetVec3(const std::string& name, float x, float y, float z) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec3(pass, name, x, y, z);
	}
}

void Material::SetVec4(const std::string& name, const glm::vec4& val) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetVec4(pass, name, val);
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

void Material::SetTexture(const std::string& name, const Texture* tex) {
	for (int pass = 0; pass < shader->passes.size(); pass++) {
		PassSetTexture(pass, name, tex);
	}
}

void Material::PassSetBool(int pass, const std::string& name, bool val) {
	uniform_buffer[pass].bools[name] = val;
}

void Material::PassSetInt(int pass, const std::string& name, int val) {
	uniform_buffer[pass].ints[name] = val;
}

void Material::PassSetFloat(int pass, const std::string& name, float val) {
	uniform_buffer[pass].floats[name] = val;
}

void Material::PassSetVec2(int pass, const std::string& name, const glm::vec2& val) {
	uniform_buffer[pass].vec2s[name] = val;
}

void Material::PassSetVec2(int pass, const std::string& name, float x, float y) {
	uniform_buffer[pass].vec2s[name] = glm::vec2(x, y);
}

void Material::PassSetVec3(int pass, const std::string& name, const glm::vec3& val) {
	uniform_buffer[pass].vec3s[name] = val;
}

void Material::PassSetVec3(int pass, const std::string& name, float x, float y, float z) {
	uniform_buffer[pass].vec3s[name] = glm::vec3(x, y, z);
}

void Material::PassSetVec4(int pass, const std::string& name, const glm::vec4& val) {
	uniform_buffer[pass].vec4s[name] = val;
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

void Material::PassSetTexture(int pass, const std::string& name, const Texture* tex) {
	uniform_buffer[pass].textures[name] = tex;
}

void Material::Apply(int pass, int unit) {
	auto pass_uniform = uniform_buffer[pass];

	for (auto& entry : pass_uniform.bools) {
		std::string name = entry.first;
		auto val = entry.second;
		glUniform1i(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), (int)val);
	}

	for (auto& entry : pass_uniform.ints) {
		std::string name = entry.first;
		auto val = entry.second;
		glUniform1i(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), val);
	}

	for (auto& entry : pass_uniform.floats) {
		std::string name = entry.first;
		auto val = entry.second;
		glUniform1f(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), val);
	}

	for (auto& entry : pass_uniform.vec2s) {
		std::string name = entry.first;
		auto val = entry.second;
		glUniform2fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, &val[0]);
	}

	for (auto& entry : pass_uniform.vec3s) {
		std::string name = entry.first;
		auto val = entry.second;
		glUniform3fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, &val[0]);
	}

	for (auto& entry : pass_uniform.vec4s) {
		std::string name = entry.first;
		auto val = entry.second;
		glUniform4fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, &val[0]);
	}

	for (auto& entry : pass_uniform.mat2s) {
		std::string name = entry.first;
		auto mat = entry.second;
		glUniformMatrix2fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	for (auto& entry : pass_uniform.mat3s) {
		std::string name = entry.first;
		auto mat = entry.second;
		glUniformMatrix3fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	for (auto& entry : pass_uniform.mat4s) {
		std::string name = entry.first;
		auto mat = entry.second;
		glUniformMatrix4fv(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	int unitIndex = 0;

	for (auto& entry : pass_uniform.textures) {
		const std::string& name = entry.first;
		const Texture* tex = entry.second;

		glActiveTexture(GL_TEXTURE0 + unitIndex);

		tex->Bind(unit);

		glUniform1i(glGetUniformLocation(shader->passes[pass]->shaderProgram, name.c_str()), unitIndex);

		unitIndex++;
	}
}