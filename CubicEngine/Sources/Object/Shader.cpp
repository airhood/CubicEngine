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
#include "../Util/Logger.h"
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

    int errorGlobal = false;

    const int SHADERLANG_NULL = 0;
    const int SHADERLANG_GLSL = 1;
    const int SHADERLANG_HLSL = 2;
    const int SHADERLANG_CG = 3;
    const int SHADERLANG_ERROR = 4;
    
    int shaderLang = SHADERLANG_NULL;

    for (auto& shaderCommand : compileResult.shaderCommands) {
        if (shaderCommand.first == "$shader_lang") {
            if (shaderCommand.second == "GLSL") {
                shaderLang = SHADERLANG_GLSL;
            }
            else if (shaderCommand.second == "HLSL") {
                shaderLang = SHADERLANG_HLSL;
            }
            else if (shaderCommand.second == "CG") {
                shaderLang = SHADERLANG_CG;
            }
            else {
                shaderLang = SHADERLANG_ERROR;
                Logger::Log(LogLevel::ERROR, "Unsupported shader language \'" + shaderCommand.second + "\'",
                    "shader_path: " + path);
                errorGlobal = true;
            }
        }
        else {
            Logger::Log(LogLevel::ERROR, "Unsupported shader command \'" + shaderCommand.first + "\'",
                "shader_path: " + path);
            errorGlobal = true;
        }
    }

    if (shaderLang == SHADERLANG_NULL) {
        Logger::Log(LogLevel::ERROR, "Shader language is undefined",
            "shader_path: " + path);
        return nullptr;
    }

    for (auto& passResult : compileResult.passResults) {
        Pass* pass = new Pass();
        std::vector<unsigned int> glShaders;
        int glShaderIndex = 0;
        bool error = false;
        for (auto& glShader : passResult.shaderPassGLShaders) {
            auto ConvertShaderType = [](std::string shaderType) {
                if (shaderType == "vertex") {
                    return GL_VERTEX_SHADER;
                }
                else if (shaderType == "fragment") {
                    return GL_FRAGMENT_SHADER;
                }
                else if (shaderType == "geometry") {
                    return GL_GEOMETRY_SHADER;
                }
                else if (shaderType == "compute") {
                    return GL_COMPUTE_SHADER;
                }
                else {
                    return 0;
                }
            };

            auto glShaderType = ConvertShaderType(glShader.type);
            if (glShaderType == 0) {
                Logger::Log(LogLevel::ERROR, "Unsupported shader type \'" + glShader.type + "\'",
                    "shader_path: " + path + ", pass: " + std::to_string(passResult.passIndex)
                    + ", shader_block: " + std::to_string(glShaderIndex));
                continue;
            }

            const char* shaderCode = glShader.code.c_str();
            int success;
            char infoLog[512];

            unsigned int shader = glCreateShader(glShaderType);
            glShaderSource(shader, 1, &shaderCode, NULL);
            glCompileShader(shader);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                Logger::Log(LogLevel::ERROR,
                    "Shader compile failed. InfoLog: " + std::string(infoLog),
                    "shader_path: " + path + ", pass: " + std::to_string(passResult.passIndex)
                    + ", shader_block: " + std::to_string(glShaderIndex));
                error = true;
                continue;
            }

            glShaders.push_back(shader);

            glShaderIndex++;
        }
        
        if (error) continue;

        pass->shaderProgram = glCreateProgram();

        for (auto& glShader : glShaders) {
            glAttachShader(pass->shaderProgram, glShader);
        }
        int success;
        char infoLog[512];
        glLinkProgram(pass->shaderProgram);
        glGetProgramiv(pass->shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            Logger::Log(LogLevel::ERROR, "Shader linking failed. InfoLog: " + std::string(infoLog),
                "shader_path: " + path);
            errorGlobal = true;
            continue;
        }

        for (auto& glShader : glShaders) {
            glDeleteShader(glShader);
        }

        shader->passes.push_back(pass);
    }

    if (errorGlobal) return nullptr;

    return shader;
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
