#pragma once

#include <GL/glew.h>
#include <glm.hpp>
#include "Color.h"

namespace CubicEngine {

    enum class Format {
        RGBA,       // 4���� ���� ä�� (Red, Green, Blue, Alpha)
        RGB,        // 3���� ���� ä�� (Red, Green, Blue)
        GRAYSCALE,  // 1���� ä�� (Gray)
    };

    class Texture abstract {
    public:
        Format format() const;
        void setCPUMemorySyncState(bool state);
        bool getCPUMemorySyncState() const;

        virtual void Apply() = 0;

    protected:
        Color* data;
        Format _format = Format::RGBA;
        bool cpuMemorySyncState = true;

        // GL
        friend class MeshRenderer;
        GLuint gl_textureID = 0;
    };
}