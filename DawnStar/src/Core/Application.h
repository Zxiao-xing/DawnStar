#pragma once

#include <Core/Momery.h>
#include <iostream>
#include "Window.h"

namespace DawnStar {
	class IApplicationWorkFlow;
	//class Window;

	class Application {
	public:
		Application(const std::string& name = "DawnStar");

		void Run();

		void Close();
	public:
		virtual ~Application() {};
	protected:
		void SetApplicationWorkFlow(IApplicationWorkFlow* applicationWorkFlow);

	private:
		bool m_isRunning = true;
		UniquePtr<IApplicationWorkFlow> m_applicationWorkFlow;
		UniquePtr<Window> m_window;
	private:
		static UniquePtr<Application> s_instance;
		static std::string s_version;
	};

	UniquePtr<Application> CreateApplication();
}