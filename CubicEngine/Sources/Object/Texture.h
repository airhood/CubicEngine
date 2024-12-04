#pragma once

#include <GL/glew.h>
#include <glm.hpp>
#include "Object.h"
#include "Color.h"

namespace CubicEngine {

    enum class TextureFormat {
        RGBA,       // 4 color channels (Red, Green, Blue, Alpha)
        RGB,        // 3 color channels (Red, Green, Blue)
        GRAYSCALE,  // 1 color channel (Gray)
    };

    class Texture abstract : public Object {
    public:
        virtual ~Texture() = default;

        void Destroy() override;

        virtual void* Clone_Obj() = 0;

        TextureFormat format() const;
        void setCPUMemorySyncState(bool state);
        bool getCPUMemorySyncState() const;

        virtual void Apply() = 0;

    protected:
        Color* data;
        TextureFormat _format = TextureFormat::RGBA;
        bool cpuMemorySyncState = true;

        // GL
        friend class MeshRenderer;
        GLuint gl_textureID = 0;
    };
}