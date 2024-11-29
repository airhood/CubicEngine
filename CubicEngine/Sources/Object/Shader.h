#pragma once

#include <GL/glew.h>
#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Pass.h"

namespace CubicEngine {

    class Shader
    {
        enum class InternalShaderType {
            VERTEX,
            FRAGMENT,
            GEOMETRY,
            COMPUTE
        };

    public:
        static Shader* Load(const std::string& path);

    private:
        std::vector<Pass> passes;

    private:
        static Shader* LoadPass(const std::string& code);

        static GLuint Load_GL_Shader(const std::string& code, InternalShaderType type);

        static void checkCompileErrors(unsigned int shader, std::string type);
    };
}