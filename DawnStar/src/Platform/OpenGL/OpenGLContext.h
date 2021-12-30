#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace DawnStar {


	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		// ͨ�� GraphicsContext �̳�
		virtual void Init() override;
		virtual void SwapBuffer() override;
	private:
		GLFWwindow* m_windowHandle;
	};

}