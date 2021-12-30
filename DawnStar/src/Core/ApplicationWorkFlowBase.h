#pragma once
#include "IApplicationWorkFlow.h"

namespace DawnStar{
	class ApplicationWorkFlowBase : public IApplicationWorkFlow {
	public:
		virtual void OnInit() override final;
		virtual void OnUpdate() override final;
		virtual void OnClose() override final;
	private:
		// 初始化各个子系统
		virtual void InternalOnInit() = 0;
		// 各个子系统的执行
		virtual void InternalOnUpdate() = 0;
		// 各个子系统的处理
		virtual void InternalOnClose() = 0;
	};
}