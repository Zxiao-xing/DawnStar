#pragma once

#include "RendererAPI.h"

namespace DawnStar {

	// 在这里设置具体的 API
	class RendererCommand {
	public:
		inline static void Init() {
			s_rendererAPI->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			s_rendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color) {
			s_rendererAPI->SetClearColor(color);
		}

		inline static void Clear() {
			s_rendererAPI->Clear();
		}

		inline static void  Draw(const SharedPtr<VertexArray>& vertexArray, uint32_t indexCount = 0) {
			s_rendererAPI->Draw(vertexArray, indexCount);
		}

		inline static RendererAPI::API GetCurRendererAPI() { 
			return s_rendererAPI->GetAPI(); 
		}
	private:
		static RendererAPI* s_rendererAPI;
	};
}