#pragma once

#include "RendererCommand.h"

namespace DawnStar {
	// ��Ⱦϵͳ��
	class RendererSys {
	public:
		static void Init();

		inline static RendererAPI::API GetCurRendererAPI() {
			return RendererCommand::GetCurRendererAPI();
		}

	private:
	};
}