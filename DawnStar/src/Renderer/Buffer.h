#pragma once

#include <iostream>
#include <vector>

namespace DawnStar {
	enum class EnShaderDataType : uint8_t{
		Unkonwn = 0,
		Bool = 1,
		Int = 2,
		Int2 = 3,
		Int3 = 4,
		Int4 = 5,
		Float = 6,
		Float2 = 7,
		Float3 = 8,
		Float4 = 9,
		Mat3 = 10,
		Mat4 = 11,
	};

	static uint32_t ShaderDataTypeByteCount(EnShaderDataType type) {
		switch (type)
		{
		case DawnStar::EnShaderDataType::Bool:		return 1;
		case DawnStar::EnShaderDataType::Int:		return 4;
		case DawnStar::EnShaderDataType::Int2:		return 4 * 2;
		case DawnStar::EnShaderDataType::Int3:		return 4 * 3;
		case DawnStar::EnShaderDataType::Int4:		return 4 * 4;
		case DawnStar::EnShaderDataType::Float:		return 4;
		case DawnStar::EnShaderDataType::Float2:	return 4 * 2;
		case DawnStar::EnShaderDataType::Float3:	return 4 * 3;
		case DawnStar::EnShaderDataType::Float4:	return 4 * 4;
		case DawnStar::EnShaderDataType::Mat3:		return 4 * 3 * 3;
		case DawnStar::EnShaderDataType::Mat4:		return 4 * 4 * 4;
		}

		return 0;
	}

	static uint32_t ShaderDataTypeComponentCount(EnShaderDataType type) {
		switch (type)
		{
		case DawnStar::EnShaderDataType::Bool:		return 1;
		case DawnStar::EnShaderDataType::Int:		return 1;
		case DawnStar::EnShaderDataType::Int2:		return 2;
		case DawnStar::EnShaderDataType::Int3:		return 3;
		case DawnStar::EnShaderDataType::Int4:		return 4;
		case DawnStar::EnShaderDataType::Float:		return 1;
		case DawnStar::EnShaderDataType::Float2:	return 2;
		case DawnStar::EnShaderDataType::Float3:	return 3;
		case DawnStar::EnShaderDataType::Float4:	return 4;
		case DawnStar::EnShaderDataType::Mat3:		return 3 * 3;
		case DawnStar::EnShaderDataType::Mat4:		return 4 * 4;
		}
		return 0;
	}

	struct BufferElement {
		bool IsNormalized;
		EnShaderDataType DataType;
		uint32_t Offset;
		uint32_t Size;
		std::string Name;

		BufferElement(EnShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), DataType(type), Size(), Offset(0), IsNormalized(normalized)
		{
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_elements(elements)
		{
			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const {
			return m_elements;
		}

		inline uint32_t GetStride() const {
			return m_stride;
		}

		std::vector<BufferElement>::iterator begin()	{ return m_elements.begin(); }
		std::vector<BufferElement>::iterator end()		{ return m_elements.end(); }
		std::vector<BufferElement>::const_iterator cbegin() const	{ return m_elements.cend(); }
		std::vector<BufferElement>::const_iterator cend() const		{ return m_elements.cend(); }

	private:
		void CalculateOffsetAndStride() {
			uint32_t offset = 0;
			m_stride = 0;
			for (auto& element : m_elements) {
				element.Offset = offset;
				offset += element.Size;
				m_stride += element.Size;
			}
		}
	private:
		uint32_t m_stride = 0;
		std::vector<BufferElement> m_elements;
	};

	class VertexBuffer {

	};

	class IndexBuffer {

	};
}