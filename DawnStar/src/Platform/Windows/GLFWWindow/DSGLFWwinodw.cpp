#include "dspch.h"
#include "DSGLFWwinodw.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace DawnStar {

	// ��������
	Window* Window::CreateWindow(const WindowProps& props) {
		return new DSGLFWWindow(props);
	}

	// �Ƿ��ʼ�� GLFW
	static bool s_isGLFWInitialized = false;

	// glfw ����ص�
	static void GLFWErrorCallback(int error, const char* desc) {
		DebugHelper::PrintError("GLFW Error (%d): %s", error, desc);
	}

	DSGLFWWindow::DSGLFWWindow(const WindowProps& props)
	{
		// ��������
		m_data.Title = props.Title;
		m_data.Width = props.Width;
		m_data.Height = props.Height;

		if (!s_isGLFWInitialized) {
			int success = glfwInit();
			DS_ASSERT_CORE(success, "Cound not intialize GLFW!");
			// ���� glfw ����ص�
			glfwSetErrorCallback(GLFWErrorCallback);
			s_isGLFWInitialized = true;
		}

		// ��������
		m_window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);

		// ����������
		m_context = new OpenGLContext(m_window);
		m_context->Init();

		// ����������һ�����ݣ��������Ի�ȡ
		glfwSetWindowUserPointer(m_window, &m_data);

		// ���ô�ֱͬ��
		SetVSync(true);
		
	}

	DSGLFWWindow::~DSGLFWWindow()
	{
		glfwDestroyWindow(m_window);
	}

	// �����߼�
	void DSGLFWWindow::InternalUpdate()
	{
		// �����߼�
		glfwPollEvents();
		// ��������
		m_context->SwapBuffer();
	}

}