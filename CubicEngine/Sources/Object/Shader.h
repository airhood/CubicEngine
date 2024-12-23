#pragma once

#include <GL/glew.h>
#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Object.h"
#include "Pass.h"

namespace CubicEngine {

    class Shader : public Object {
        enum class InternalShaderType {
            VERTEX,
            FRAGMENT,
            GEOMETRY,
            COMPUTE
        };

    public:
        ~Shader();

        void Destroy() override;

    private:
        Shader() = default;
        void* Clone_Obj() override;

    public:
        static Shader* Load(const std::string& path);

    private:
        friend class Material;
        friend class Renderer;
        std::vector<Pass*> passes;

    private:
        static GLuint Load_GL_Shader(const std::string& code, InternalShaderType type);

        static void checkCompileErrors(unsigned int shader, std::string type);
    };
}