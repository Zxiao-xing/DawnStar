#pragma once

#include <Core/Momery.h>

namespace DawnStar {
	enum class EnInternalFormat {
		Unknown,
		RGBA8,
		RGBA32F,
		RGB8,
	};

	enum class EnDataFormat {
		Unknown,
		RGBA,
		RGB,
	};

	class Texture {
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void UnBind() const = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture {
	public:
		virtual ~Texture2D() = default;

		static SharedPtr<Texture2D> Create(uint32_t width, uint32_t height, EnInternalFormat internalFormat, EnDataFormat dataFormat);
		static SharedPtr<Texture2D> Create(const std::string& path);
	};
}