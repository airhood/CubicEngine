#pragma once

#include <GL/glew.h>
#include <glm.hpp>
#include "Color.h"

namespace CubicEngine {

    enum class Format {
        RGBA,       // 4개의 색상 채널 (Red, Green, Blue, Alpha)
        RGB,        // 3개의 색상 채널 (Red, Green, Blue)
        GRAYSCALE,  // 1개의 채널 (Gray)
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