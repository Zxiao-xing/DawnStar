#pragma once

#include <Core/Window.h>


namespace DawnStar {
	class WindowsWindow : public Window {
	public:
		virtual ~WindowsWindow() = default;

		virtual void Update() override final {
			InternalUpdate();
		}

		virtual uint32_t GetWidth() const override final {
			return m_data.Width;
		}

		virtual uint32_t GetHeight() const override final {
			return m_data.Height;
		}

		virtual void SetVSync(bool enabled) override final {
			m_data.IsVSync = enabled;
			InternalSetVSync();
		}

		virtual bool IsVSync() const override final {
			return m_data.IsVSync;
		}
	private:
		virtual void InternalSetVSync() = 0;
		virtual void InternalUpdate() = 0;
	protected:
		struct WindowData {
			std::string Title;
			uint32_t Width, Height;
			bool IsVSync;
		};
		WindowData m_data;
	};
}