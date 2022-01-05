#include "dspch.h"
#include "Texture.h"

#include "RendererSys.h"
#include <Platform/OpenGL/OpenGLTexture2D.h>

namespace DawnStar {
    SharedPtr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, EnInternalFormat internalFormat, EnDataFormat dataFormat)
    {
		switch (RendererSys::GetCurRendererAPI())
		{
		case RendererAPI::API::None:
			DS_ASSERT_CORE(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLTexture2D>(width, height, internalFormat, dataFormat);
		default:
			DS_ASSERT_CORE(false, "Unknown Renderer API");
			return nullptr;
		}
    }

    SharedPtr<Texture2D> Texture2D::Create(const std::string& path)
    {
		switch (RendererSys::GetCurRendererAPI())
		{
		case RendererAPI::API::None:
			DS_ASSERT_CORE(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLTexture2D>(path);
		default:
			DS_ASSERT_CORE(false, "Unknown Renderer API");
			return nullptr;
		}
    }
}