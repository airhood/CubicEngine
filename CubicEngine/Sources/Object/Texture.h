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

        virtual void* Clone_Obj() const = 0;

        TextureFormat format() const;
        void setCPUMemorySyncState(bool state);
        bool getCPUMemorySyncState() const;

        virtual void Apply() = 0;

    protected:
        Color* data;
        unsigned char* data_raw;
        TextureFormat _format = TextureFormat::RGBA;
        bool cpuMemorySyncState = true;

        // GL
        friend class MeshRenderer;
        friend class Renderer;
        GLuint gl_textureID = 0;

        virtual void SyncMemory() = 0;

        friend class Renderer;
        friend class Renderer2D;
        friend class Material;
        void Bind(int unit) const;
    };
}