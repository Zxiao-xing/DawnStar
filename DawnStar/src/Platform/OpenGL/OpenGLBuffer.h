#pragma once

#include <Renderer/Buffer.h>

namespace DawnStar {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
	public:
		virtual ~OpenGLVertexBuffer();

		virtual const BufferLayout& GetLayout() const override {
			return m_layout;
		}

		virtual void SetLayout(const BufferLayout& layout) override {
			m_layout = layout;
		}

		virtual void SetData(const void* data, uint32_t size) override;

		virtual void Bind() const override;

		virtual void UnBind() const override;
	private:
		uint32_t m_rendererID;
		BufferLayout m_layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
	public:
		virtual ~OpenGLIndexBuffer();

		virtual uint32_t GetCount() const override {
			return m_count;
		}

		virtual void Bind() const override;
		virtual void UnBind() const override;
	private:
		uint32_t m_rendererID;
		uint32_t m_count;
	};
}