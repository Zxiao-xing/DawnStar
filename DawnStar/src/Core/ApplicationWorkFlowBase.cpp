#include "dspch.h"
#include "ApplicationWorkFlowBase.h"

#include "Renderer/RendererSys.h"

namespace DawnStar {
	void ApplicationWorkFlowBase::OnInit()
	{
		// 渲染系统初始化
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
