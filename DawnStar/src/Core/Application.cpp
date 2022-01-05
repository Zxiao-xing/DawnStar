#include "dspch.h"
#include "Application.h"
#include "IApplicationWorkFlow.h"

namespace DawnStar {
	UniquePtr<Application> Application::s_instance = nullptr;
	std::string Application::s_version = "1.0.0.0";

	Application::Application(const std::string& name)
	{
		DS_ASSERT_CORE(s_instance == nullptr, "Application already exists!");
		s_instance = CreateUniqueByPtr(this);
		// ��������
		m_window = CreateUniqueByPtr(Window::CreateWindow());

		DebugHelper::PrintMsg("Application Init. version:{0}", s_version);

		m_applicationWorkFlow = nullptr;
	}

	void Application::Run()
	{
		while (m_isRunning) {
			// ��ϵͳ����
			if (m_applicationWorkFlow != nullptr) {
				m_applicationWorkFlow->OnUpdate();
			}
			// ˢ�´���
			m_window->Update();
		}
	}

	void Application::Close()
	{
		m_isRunning = false;
		if (m_applicationWorkFlow != nullptr) {
			m_applicationWorkFlow->OnClose();
		}
	}

	void Application::SetApplicationWorkFlow(IApplicationWorkFlow* applicationWorkFlow)
	{
		if (m_applicationWorkFlow != nullptr) {
			m_applicationWorkFlow->OnClose();
		}

		m_applicationWorkFlow = CreateUniqueByPtr(applicationWorkFlow);
		m_applicationWorkFlow->OnInit();
	}

}