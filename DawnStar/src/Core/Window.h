#pragma once
#include <iostream>
#include <Core/Momery.h>

namespace DawnStar {
	struct WindowProps {
		std::string Title;
		std::uint32_t Width, Height;

		WindowProps(const std::string& title = "DawnStar", std::uint32_t width = 1280, std::uint32_t height = 960)
			:Title(title), Width(width), Height(height)
		{
		}
	};

	class Window {
	public:
		virtual ~Window() = default;
		virtual void Update() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* CreateWindow(const WindowProps& props = WindowProps());
	};
}