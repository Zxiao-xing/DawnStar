#include "dspch.h"
#include "Shader.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace DawnStar {
	ShaderType String2ShaderType(const std::string& typeStr) {
		if (typeStr == "vertex") {
			return ShaderType::Vertex;
		}
		else if (typeStr == "fragment") {
			return ShaderType::Fragment;
		}
		else if (typeStr == "compute") {
			return ShaderType::Compute;
		}
		return ShaderType::Unknown;
	}

	SharedPtr<Shader> Shader::CreateShader(const std::string& filePath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			DS_ASSERT_CORE(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLShader>(filePath);
		default:
			DS_ASSERT_CORE(false, "Unknown Renderer API");
			return nullptr;
		}
	}


	void ShaderLibrary::Add(const SharedPtr<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const std::string& name, const SharedPtr<Shader>& shader)
	{
		DS_ASSERT_CORE(!IsExistShader(name), "Shader already exist! name:{0}", name);
		m_shaderMap[name] = shader;
	}

	SharedPtr<Shader> ShaderLibrary::LoadShader(const std::string& filePath, ShaderType type)
	{
		auto shader = Shader::CreateShader(filePath);
		Add(shader);
		return shader;
	}

	SharedPtr<Shader> ShaderLibrary::LoadShader(const std::string& name, const std::string& filePath, ShaderType type)
	{
		auto shader = Shader::CreateShader(filePath);
		Add(name, shader);
		return shader;
	}

	SharedPtr<Shader> ShaderLibrary::GetShader(const std::string& name)
	{
		return m_shaderMap[name];
	}

	bool ShaderLibrary::IsExistShader(const std::string& name) const
	{
		return m_shaderMap.find(name) != m_shaderMap.end();
	}
}

