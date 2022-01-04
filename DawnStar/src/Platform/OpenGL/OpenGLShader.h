#pragma once
#include <Renderer/Shader.h>

namespace DawnStar {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& filePath);

		~OpenGLShader();
	public:
		virtual void Bind() const override;

		virtual void UnBind() const override;

		virtual const std::string& GetName() const override {
			return m_name;
		}
	private:
		std::unordered_map<ShaderType, std::string> PreProcess(const std::string& source, const std::string& filePath);
		void Compile(const std::unordered_map<ShaderType, std::string>& shaderSourceMap);
	private:
		uint32_t m_rendererID;
		ShaderType type;
		std::string m_name;
	};
}