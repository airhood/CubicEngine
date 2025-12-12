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

    enum class TextureType {
        ALBEDO,
        NORMAL,
        METALLIC,
        ROUGHNESS,
        AO,
        EMISSION,
        SPRITE,
        SHADOW_MAP,
        SHADOW_CUBE,
        GBUFFER_DEPTH,
        GBUFFER_NORMAL,
        IRRADIANCE_MAP,
        PREFILTER_MAP,
        BRDF_LUT,
        POSTFX_0,
        POSTFX_1
    };

    class Texture abstract : public Object {
    public:
        virtual ~Texture() = default;

        virtual void* Clone_Obj() const = 0;

        TextureFormat format() const;

        void SetTextureType(TextureType textureType);
        TextureType GetTextureType() const;

        void setCPUMemorySyncState(bool state);
        bool getCPUMemorySyncState() const;

        virtual void Apply() = 0;

    protected:
        Color* data;

        friend class TextureManager;
        unsigned char* data_raw;

        TextureFormat _format = TextureFormat::RGBA;
        bool cpuMemorySyncState = true;

        TextureType textureType = TextureType::ALBEDO;

        // GL
        friend class MeshRenderer;
        friend class Renderer;

        virtual void SyncMemory() = 0;

        friend class Renderer;
        friend class Renderer2D;
        friend class Material;

        int layerIndex = -1;
    };
}