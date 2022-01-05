#include "dspch.h"
#include "OpenGLTexture2D.h"

#include "OpenGLUtils.h"
#include <glad/glad.h>
#include <stb_image.h>

namespace DawnStar {


    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, EnInternalFormat internalFormat, EnDataFormat dataFormat)
        :m_width(width), m_height(height)
    {
        m_internalFormat = internalFormat;
        m_dataFormat = dataFormat;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, OpenGLConvert::InternalFormat2GLenum(m_internalFormat), m_width, m_height);

        // Todo£º»»³ÉÃ¶¾Ù
        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        :m_path(path)
    {
        stbi_set_flip_vertically_on_load(false);
        int width, height, channels;
        stbi_uc* data = nullptr;
        data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        DS_ASSERT_CORE(data != nullptr, "Failed to load image");
        m_width = width;
        m_height = height;

        m_internalFormat = EnInternalFormat::Unknown;
        m_dataFormat = EnDataFormat::Unknown;

        if (channels == 4) {
            m_internalFormat = EnInternalFormat::RGBA8;
            m_dataFormat = EnDataFormat::RGBA;
        }
        else if (channels == 3) {
            m_internalFormat = EnInternalFormat::RGB8;
            m_dataFormat = EnDataFormat::RGB;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, OpenGLConvert::InternalFormat2GLenum(m_internalFormat), m_width, m_height);

        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, OpenGLConvert::DataFormat2GLenum(m_dataFormat), GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_rendererID);
    }

    void OpenGLTexture2D::SetData(void* data, uint32_t size)
    {
        uint32_t bpc = m_dataFormat == EnDataFormat::RGBA ? 4 : 3;
        DS_ASSERT_CORE(size == m_width * m_height * bpc, "Data must be entire texutre");
        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, OpenGLConvert::DataFormat2GLenum(m_dataFormat), GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_rendererID);
    }

    void OpenGLTexture2D::UnBind() const
    {
        glBindTextureUnit(GL_TEXTURE_2D, 0);
    }
}
