#include "dspch.h"
#include "DSGLFWwinodw.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace DawnStar {

	// 创建窗口
	Window* Window::CreateWindow(const WindowProps& props) {
		return new DSGLFWWindow(props);
	}

	// 是否初始化 GLFW
	static bool s_isGLFWInitialized = false;

	// glfw 错误回调
	static void GLFWErrorCallback(int error, const char* desc) {
		DebugHelper::PrintError("GLFW Error (%d): %s", error, desc);
	}

	DSGLFWWindow::DSGLFWWindow(const WindowProps& props)
	{
		// 缓存数据
		m_data.Title = props.Title;
		m_data.Width = props.Width;
		m_data.Height = props.Height;

		if (!s_isGLFWInitialized) {
			int success = glfwInit();
			DS_ASSERT_CORE(success, "Cound not intialize GLFW!");
			// 设置 glfw 错误回调
			glfwSetErrorCallback(GLFWErrorCallback);
			s_isGLFWInitialized = true;
		}

		// 创建窗口
		m_window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);

		// 创建上下文
		m_context = new OpenGLContext(m_window);
		m_context->Init();

		// 给窗口设置一个数据，后续可以获取
		glfwSetWindowUserPointer(m_window, &m_data);

		// 设置垂直同步
		SetVSync(true);
		
	}

	DSGLFWWindow::~DSGLFWWindow()
	{
		glfwDestroyWindow(m_window);
	}

	// 更新逻辑
	void DSGLFWWindow::InternalUpdate()
	{
		// 处理逻辑
		glfwPollEvents();
		// 交换缓冲
		m_context->SwapBuffer();
	}

}