#include "dspch.h"
#include "ApplicationWorkFlowBase.h"

#include "Renderer/RendererSys.h"

namespace DawnStar {
	void ApplicationWorkFlowBase::OnInit()
	{
		// ��Ⱦϵͳ��ʼ��
		RendererSys::Init();

		InternalOnInit();
	}

	void ApplicationWorkFlowBase::OnUpdate()
	{
		InternalOnUpdate();
	}

	void ApplicationWorkFlowBase::OnClose()
	{
		InternalOnClose();
	}

}
