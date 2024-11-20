#pragma once

#include <GL/glew.h>
#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace CubicEngine {
    class Shader
    {
    public:
        static Shader* Load(const std::string& path);

    private:
        friend class Material;
        friend class RenderManager;
        GLuint ID;

    private:
        void checkCompileErrors(unsigned int shader, std::string type);
    };
}