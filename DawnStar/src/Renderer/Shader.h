#pragma once

#include <string>
#include <Core/Momery.h>
#include <unordered_map>

namespace DawnStar {
	enum class ShaderType : uint8_t {
		Unknown,
		Vertex,
		Fragment,
		Compute,
	};

	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const std::string& GetName() const = 0;

		static SharedPtr<Shader> CreateShader(const std::string& filePath);

	private:
		ShaderType m_shaderType;
	};

	class ShaderLibrary {
	public:
		void Add(const SharedPtr<Shader>& shader);
		void Add(const std::string& name, const SharedPtr<Shader>& shader);

		SharedPtr<Shader> LoadShader(const std::string& filePath, ShaderType type);
		SharedPtr<Shader> LoadShader(const std::string& name, const std::string& filePath, ShaderType type);

		SharedPtr<Shader> GetShader(const std::string& name);

		bool IsExistShader(const std::string& name) const;
	private:
		std::unordered_map<std::string, SharedPtr<Shader>> m_shaderMap;
	};

	ShaderType String2ShaderType(const std::string& typeStr);
}