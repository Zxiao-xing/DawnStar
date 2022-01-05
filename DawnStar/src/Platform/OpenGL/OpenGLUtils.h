#pragma once
#include <iostream>
#include <glad/glad.h>
#include <Renderer/Texture.h>

namespace DawnStar {
	class OpenGLConvert {
	public:
		static std::string GLubytePtr2Str(const GLubyte* ubytePtr) {
			return std::string(ubytePtr, ubytePtr + sizeof(ubytePtr) / sizeof(ubytePtr[0]));
		}

		static GLenum InternalFormat2GLenum(EnInternalFormat internalFormat) {
			switch (internalFormat)
			{
			case EnInternalFormat::RGBA8:
				return GL_RGBA8;
			case EnInternalFormat::RGB8:
				return GL_RGB8;
			case EnInternalFormat::RGBA32F:
				return GL_RGBA32F;
			}
			DS_ASSERT_CORE(false, "Unkonwn interal format");
			return 0;
		}

		static GLenum DataFormat2GLenum(EnDataFormat dataFormat) {
			switch (dataFormat)
			{
			case EnDataFormat::RGBA:
				return GL_RGBA;
			case EnDataFormat::RGB:
				return GL_RGB;
			}
			DS_ASSERT_CORE(false, "Unkonwn data format");
			return 0;
		}

	};
}