#pragma once

#include <Renderer/VertexArray.h>

namespace DawnStar {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
	public:
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;

		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const SharedPtr<VertexBuffer>& vertexBuffer) override;

		virtual void SetIndexBuffer(const SharedPtr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<SharedPtr<VertexBuffer>>& GetVertexBuffer() const override {
			return m_vertexBuffers;
		}

		virtual const SharedPtr<IndexBuffer>& GetIndexBuffer() const override {
			return m_indexBuffer;
		}
	private:
		uint32_t m_rendererID;
		uint32_t m_vertexBufferIndex = 0;

		SharedPtr<IndexBuffer> m_indexBuffer;
		std::vector<SharedPtr<VertexBuffer>> m_vertexBuffers;
	};
}