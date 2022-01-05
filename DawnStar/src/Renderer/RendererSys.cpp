#include "dspch.h"
#include "RendererSys.h"

namespace DawnStar {
	void RendererSys::Init()
	{
		DebugHelper::PrintMsg("Init Renderer System");
		RendererCommand::Init();
		DebugHelper::PrintMsg("Compelete Init");
	}
}