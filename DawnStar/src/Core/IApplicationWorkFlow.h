#pragma once

namespace DawnStar {
	class IApplicationWorkFlow {
	public:
		virtual void OnInit() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnClose() = 0;
	};
}