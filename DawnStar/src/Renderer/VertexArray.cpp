#include "dspch.h"
#include "VertexArray.h"
#include "RendererSys.h"
#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace DawnStar {

	SharedPtr<VertexArray> VertexArray::CreateVertexArray()
	{
		switch (RendererSys::GetCurRendererAPI())
		{
		case RendererAPI::API::None:
			DS_ASSERT_CORE(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLVertexArray>();
		default:
			DS_ASSERT_CORE(false, "Unknown Renderer API");
			return nullptr;
		}
	}

}

