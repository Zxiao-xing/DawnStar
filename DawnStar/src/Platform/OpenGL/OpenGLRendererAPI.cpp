#include "dspch.h"
#include "OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace DawnStar {
	OpenGLRendererAPI::OpenGLRendererAPI()
		: RendererAPI(API::OpenGL)
	{
	}
	void OpenGLRendererAPI::Init()
	{
		// ÅäÖÃOpenGLµÄÆ¬Ôª²âÊÔ½×¶Î
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		// 
		glClear(GL_COLOR_BUFFER_BIT);
	}
}