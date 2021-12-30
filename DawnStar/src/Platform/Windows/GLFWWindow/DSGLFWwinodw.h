#pragma once

#include <Platform/Windows/WindowsWindow.h>
#include <GLFW/glfw3.h>

namespace DawnStar {
	class GraphicsContext;

	class DSGLFWWindow : public WindowsWindow {
	public:
		DSGLFWWindow(const WindowProps& props);
		
		virtual ~DSGLFWWindow();

	private:
		virtual void InternalSetVSync() override {
			if (m_data.IsVSync) {
				glfwSwapInterval(1);
			}
			else {
				glfwSwapBuffers(0);
			}
		}

		virtual void InternalUpdate() override;

	private:
		GLFWwindow* m_window;
		GraphicsContext* m_context;
	};
}