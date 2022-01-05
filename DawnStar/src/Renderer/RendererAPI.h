#pragma once

#include <iostream>
#include <glm/glm.hpp>

namespace DawnStar {

	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1,
		};
	public:
		RendererAPI(API api);
	public:
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		// 渲染系统内部通过该接口获取当前使用 API
		inline API GetAPI() { return m_API; }
	protected:
		API m_API;
	};
}