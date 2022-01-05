#include "dspch.h"
#include "OpenGLShader.h"
#include "File/FileManager.h"

#include "glad/glad.h"

namespace DawnStar {
	static GLenum ShaderType2GLType(ShaderType type) {
		switch (type)
		{
		case ShaderType::Vertex:
			return GL_VERTEX_SHADER;
		case ShaderType::Fragment:
			return GL_FRAGMENT_SHADER;
		case ShaderType::Compute:
			return GL_COMPUTE_SHADER;
		}
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filePath)
	{
		std::string source = FileManager::ReadFile(filePath);
		auto shaderSourceMap = PreProcess(source, filePath);
		Compile(shaderSourceMap);

		auto lastSlash = filePath.find_last_of("/\\");
		lastSlash == std::string::npos ? 0 : lastSlash += 1;
		auto lastDot = filePath.rfind(".");
		auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
		m_name = filePath.substr(lastSlash, count);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_rendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_rendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	std::unordered_map<ShaderType, std::string> OpenGLShader::PreProcess(const std::string& source, const std::string& filePath)
	{
		std::unordered_map<ShaderType, std::string> shaderSourceMap;

		// shader 文件用 #type 标识相应的 shader 类型
		const char* typeToken = "#type";
		size_t typeTockLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t col = source.find_first_of("\r\n", pos);
			DS_ASSERT_CORE(col != std::string::npos, "shader source syntax error! file: {0}", filePath);

			size_t begin = pos + typeTockLength + 1;
			std::string type = source.substr(begin, col - begin);
			ShaderType shaderType = String2ShaderType(type);
			DS_ASSERT_CORE(shaderType != ShaderType::Unknown, "Invalid shader type specified in file: {0}", filePath);

			size_t nextLinePos = source.find_first_not_of("\r\n", col);
			pos = source.find(typeToken, nextLinePos);
			// 目前只支持一个文件中对于一种类型的 shader 只存在一个
			shaderSourceMap[shaderType] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}
		return shaderSourceMap;
	}

	void OpenGLShader::Compile(const std::unordered_map<ShaderType, std::string>& shaderSourceMap)
	{
		GLuint program = glCreateProgram();

		std::vector<GLenum> glShaderIDs;

		for (auto& kv : shaderSourceMap) {
			GLenum type = ShaderType2GLType(kv.first);
			const std::string& source = kv.second;
			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				DebugHelper::PrintError("{0}", infoLog.data());
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);
		}
		m_rendererID = program;

		glLinkProgram(program);

		GLuint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			for (auto id : glShaderIDs) {
				glDeleteShader(id);
			}

			DebugHelper::PrintError("{0}", infoLog.data());
			return;
		}

		for (auto id : glShaderIDs) {
			glDetachShader(program, id);
		}
	}
}