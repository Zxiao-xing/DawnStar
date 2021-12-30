#include "dspch.h"
#include "ApplicationWorkFlowBase.h"


namespace DawnStar {
	void ApplicationWorkFlowBase::OnInit()
	{
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
