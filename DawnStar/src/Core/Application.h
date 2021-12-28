#pragma once

#include <Core/Momery.h>

#include <iostream>

namespace DawnStar {
	class Application {
	public:
		Application(const std::string& name = "DawnStar");

		void Run();

		void Close();
	public:
		virtual ~Application() {};
	private:
		bool m_isRunning = true;
	private:
		static UniquePtr<Application> s_instance;
		static std::string s_version;
	};

	UniquePtr<Application> CreateApplication();
}