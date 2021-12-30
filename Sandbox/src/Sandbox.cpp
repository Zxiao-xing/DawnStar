#pragma once

#include <DawnStar.h>
#include <Core/EntryPoint.h>

namespace DawnStar {
	class SandboxWorkFlow : public ApplicationWorkFlowBase {
		// Í¨¹ý ApplicationWorkFlowBase ¼Ì³Ð
		virtual void InternalOnInit() override
		{

		}
		virtual void InternalOnUpdate() override
		{
		}
		virtual void InternalOnClose() override
		{
		}
	private:

	};

	class Sandbox : public Application {
	public:
		Sandbox() {
			SetApplicationWorkFlow(new SandboxWorkFlow());
		}
	};

	UniquePtr<Application> CreateApplication() {
		return CreateUniqueByPtr(new Sandbox());
	}
}
