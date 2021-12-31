#include "dspch.h"
#include "Shader.h"
#include "RendererAPI.h"

namespace DawnStar{
    SharedPtr<Shader> Shader::CreateShader(const std::string& filePath, ShaderType type)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None:
            DS_ASSERT_CORE(false, "RendererAPI::None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OpenGL:
            return CreateShared<Shader>(filePath);
            break;
        default:
            break;
        }
    }

    SharedPtr<Shader> Shader::CreateShader(const std::string& name, const std::string& filePath, ShaderType type)
    {
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
        auto shader = Shader::CreateShader(filePath, type);
        Add(shader);
        return shader;
    }

    SharedPtr<Shader> ShaderLibrary::LoadShader(const std::string& name, const std::string& filePath, ShaderType type)
    {
        auto shader = Shader::CreateShader(filePath, type);
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

