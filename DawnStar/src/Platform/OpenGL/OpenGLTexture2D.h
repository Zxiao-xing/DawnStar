#pragma once

#include <Renderer/Texture.h>


namespace DawnStar {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height, EnInternalFormat internalFormat, EnDataFormat dataFormat);
		OpenGLTexture2D(const std::string& path);
	public:
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override {
			return m_width;
		}
		virtual uint32_t GetHeight() const override {
			return m_height;
		}
		virtual uint32_t GetRendererID() const override {
			return m_rendererID;
		}

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;
		virtual void UnBind() const override;
	private:
		uint32_t m_height, m_width;
		uint32_t m_rendererID;
		EnInternalFormat m_internalFormat;
		EnDataFormat m_dataFormat;

		std::string m_path;

		virtual bool operator==(const Texture& other) const override {
			return m_rendererID == ((OpenGLTexture2D&)other).m_rendererID;
		}
	};
}