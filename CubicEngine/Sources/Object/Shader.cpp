#include "shader.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include "../Util/ShaderCompiler.h"

using namespace CubicEngine;

Shader::~Shader() {

}

void Shader::Destroy() {

}

void* Shader::Clone_Obj() {
    return nullptr;
}

Shader* Shader::Load(const std::string& path) {
    std::ifstream file;
    std::string code;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        code = stream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        return nullptr;
    }

    auto compileResult = ShaderCompiler::Compile_csl(code);

    if (compileResult.error) return nullptr;

    Shader* shader = new Shader();

    const int GLSL = 0;
    const int HLSL = 1;
    const int CG = 2;
    
    int shaderLang;

    auto applyShaderCommands = [&]() -> bool {
        for (auto& shaderCommand : compileResult.shaderCommands) {
            if (shaderCommand.first == "$shader_lang") {
                if (shaderCommand.second == "GLSL") {
                    shaderLang = GLSL;
                }
                else if (shaderCommand.second == "HLSL") {
                    shaderLang = HLSL;
                }
                else if (shaderCommand.second == "CG") {
                    shaderLang = CG;
                }
                else {
                    // TODO: throw error
                    return false;
                }
            }
            else {
                // TODO: throw error
                return false;
            }
        }
    };

    return nullptr;
}

GLuint Shader::Load_GL_Shader(const std::string& code, InternalShaderType type) {
    const char* code_ = code.c_str();

    GLenum gl_shaderType;
    std::string str_shaderType;
    switch (type) {
        case InternalShaderType::VERTEX:
            gl_shaderType = GL_VERTEX_SHADER;
            str_shaderType = "VERTEX";
            break;
        case InternalShaderType::FRAGMENT:
            gl_shaderType = GL_FRAGMENT_SHADER;
            str_shaderType = "FRAGMENT";
            break;
        case InternalShaderType::GEOMETRY:
            gl_shaderType = GL_GEOMETRY_SHADER;
            str_shaderType = "GEOMETRY";
            break;
        case InternalShaderType::COMPUTE:
            gl_shaderType = GL_COMPUTE_SHADER;
            str_shaderType = "COMPUTE";
            break;
        default:
            return 0;
    }

    GLuint shader;
    shader = glCreateShader(gl_shaderType);
    glShaderSource(shader, 1, &code_, NULL);
    glCompileShader(shader);
    checkCompileErrors(shader, str_shaderType);

    return shader;
}

void Shader::checkCompileErrors(GLuint shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
