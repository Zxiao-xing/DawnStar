#pragma once

#include "RendererCommand.h"

namespace DawnStar {
	// ‰÷»æœµÕ≥¿‡
	class RendererSys {
	public:
		static void Init();

		inline static void Draw(const SharedPtr<VertexArray>& vertexArray, uint32_t indexCount = 0) {
			RendererCommand::Draw(vertexArray, indexCount);
		}

		inline static RendererAPI::API GetCurRendererAPI() {
			return RendererCommand::GetCurRendererAPI();
		}

	private:
	};
}