#pragma once
#include <iostream>
#include <glad/glad.h>

namespace DawnStar {
	class OpenGLUtils {
	public:
		static std::string GLubytePtr2Str(const GLubyte* ubytePtr) {
			return std::string(ubytePtr, ubytePtr + sizeof(ubytePtr) / sizeof(ubytePtr[0]));
		}
	};
}