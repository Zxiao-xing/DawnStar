#include "dspch.h"
#include "Application.h"

namespace DawnStar {
	UniquePtr<Application> Application::s_instance = nullptr;
	std::string Application::s_version = "1.0.0.0";

	DawnStar::Application::Application(const std::string& name)
	{
		DS_ASSERT_CORE(s_instance == nullptr, "Application already exists!");
		s_instance = CreateUniqueByPtr(this);

		DebugHelper::PrintMsg("Application Init. version:{0}", s_version);
	}

	void DawnStar::Application::Run()
	{
		while (m_isRunning) {

		}
	}

	void DawnStar::Application::Close()
	{
		m_isRunning = false;
	}

}