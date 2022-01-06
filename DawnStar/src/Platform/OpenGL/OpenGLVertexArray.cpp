#include "dspch.h"
#include "OpenGLVertexArray.h"
#include "OpenGLUtils.h"
#include <glad/glad.h>

namespace DawnStar {
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_rendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_rendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_rendererID);
    }

    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const SharedPtr<VertexBuffer>& vertexBuffer)
    {
        DS_ASSERT_CORE(vertexBuffer->GetLayout().GetElements().size() != 0, "Vertex buffer has no layout!");

        glBindVertexArray(m_rendererID);
        vertexBuffer->Bind();
        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout) {
            switch (element.DataType)
            {
            case EnShaderDataType::Bool:
            case EnShaderDataType::Int:
            case EnShaderDataType::Int2:
            case EnShaderDataType::Int3:
            case EnShaderDataType::Int4:
                glEnableVertexAttribArray(m_vertexBufferIndex);
                glVertexAttribIPointer(m_vertexBufferIndex, ShaderDataTypeComponentCount(element.DataType), OpenGLConvert::ShaderDataType2GLenum(element.DataType), layout.GetStride(), (const void*)element.Offset);
                m_vertexBufferIndex++;
                break;
            case EnShaderDataType::Float:
            case EnShaderDataType::Float2:
            case EnShaderDataType::Float3:
            case EnShaderDataType::Float4:
                glEnableVertexAttribArray(m_vertexBufferIndex);
                glVertexAttribPointer(m_vertexBufferIndex, ShaderDataTypeComponentCount(element.DataType), OpenGLConvert::ShaderDataType2GLenum(element.DataType), element.IsNormalized, layout.GetStride(), (const void*)element.Offset);
                m_vertexBufferIndex++;
                break;
            case EnShaderDataType::Mat3:
            case EnShaderDataType::Mat4:
                uint8_t count = ShaderDataTypeComponentCount(element.DataType);
                for (uint8_t i = 0; i < count; i++) {
                    glEnableVertexAttribArray(m_vertexBufferIndex);
                    glVertexAttribPointer(m_vertexBufferIndex, count, OpenGLConvert::ShaderDataType2GLenum(element.DataType), element.IsNormalized, layout.GetStride(), (const void*)(element.Offset + sizeof(float) * count * i));
                    glVertexAttribDivisor(m_vertexBufferIndex, 1);
                    m_vertexBufferIndex++;
                }
                break;
            }
        }
        m_vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const SharedPtr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_rendererID);
        indexBuffer->Bind();
        m_indexBuffer = indexBuffer;
    }
}