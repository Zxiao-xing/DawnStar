#pragma once

#include <iostream>

namespace DawnStar {

	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1,
		};
	public:
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor() = 0;
		virtual void Clear() = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}