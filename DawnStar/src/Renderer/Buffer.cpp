#include "dspch.h"
#include "Buffer.h"
#include "RendererSys.h"
#include <Platform/OpenGL/OpenGLBuffer.h>

namespace DawnStar {
	SharedPtr<VertexBuffer> VertexBuffer::CreateVertexBuffer(uint32_t size)
	{
		switch (RendererSys::GetCurRendererAPI())
		{
		case RendererAPI::API::None:
			DS_ASSERT_CORE(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLVertexBuffer>(size);
		default:
			DS_ASSERT_CORE(false, "Unknown Renderer API");
			return nullptr;
		}
	}

	SharedPtr<VertexBuffer> VertexBuffer::CreateVertexBuffer(float* vertices, uint32_t size)
	{
		switch (RendererSys::GetCurRendererAPI())
		{
		case RendererAPI::API::None:
			DS_ASSERT_CORE(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLVertexBuffer>(vertices, size);
		default:
			DS_ASSERT_CORE(false, "Unknown Renderer API");
			return nullptr;
		}
	}

	SharedPtr<IndexBuffer> IndexBuffer::CreateIndexBuffer(uint32_t* indices, uint32_t count)
	{
		switch (RendererSys::GetCurRendererAPI())
		{
		case RendererAPI::API::None:
			DS_ASSERT_CORE(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLIndexBuffer>(indices, count);
		default:
			DS_ASSERT_CORE(false, "Unknown Renderer API");
			return nullptr;
		}
	}
}
