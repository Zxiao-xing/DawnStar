#pragma once
#include "IApplicationWorkFlow.h"

namespace DawnStar{
	class ApplicationWorkFlowBase : public IApplicationWorkFlow {
	public:
		virtual void OnInit() override final;
		virtual void OnUpdate() override final;
		virtual void OnClose() override final;
	private:
		// ��ʼ��������ϵͳ
		virtual void InternalOnInit() = 0;
		// ������ϵͳ��ִ��
		virtual void InternalOnUpdate() = 0;
		// ������ϵͳ�Ĵ���
		virtual void InternalOnClose() = 0;
	};
}