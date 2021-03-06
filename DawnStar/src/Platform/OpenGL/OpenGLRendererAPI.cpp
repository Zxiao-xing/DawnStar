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
		// ????OpenGL??ƬԪ???Խ׶?
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
	void OpenGLRendererAPI::Draw(const SharedPtr<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount == 0 ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}