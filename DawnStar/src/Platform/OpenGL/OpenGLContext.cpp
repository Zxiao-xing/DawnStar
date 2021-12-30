#include "dspch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <Platform/OpenGL/OpenGLUtils.h>

namespace DawnStar {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		//DS_ASSERT_CORE(windowHandle, "OpenGLContext Error: window handle is null");
	}

	void OpenGLContext::Init()
	{
		// ���õ�ǰ������
		glfwMakeContextCurrent(m_windowHandle);

		// ��ʼ�� Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DS_ASSERT_CORE(status, "Failed to initialize Glad!");
		
		// ��� OpenGL �汾��Ϣ
		DebugHelper::PrintMsg("OpenGL Info:");

		DebugHelper::PrintMsg("\tVendor:{0}", OpenGLUtils::GLubytePtr2Str(glGetString(GL_VENDOR)));
		DebugHelper::PrintMsg("\tRenderer:{0}", OpenGLUtils::GLubytePtr2Str(glGetString(GL_RENDERER)));
		DebugHelper::PrintMsg("\tVersion:{0}", OpenGLUtils::GLubytePtr2Str(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}


