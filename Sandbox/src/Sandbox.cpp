#pragma once

#include <DawnStar.h>
#include <Core/EntryPoint.h>
#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <Platform/OpenGL/OpenGLShader.h>

namespace DawnStar {

	class SandboxWorkFlow : public ApplicationWorkFlowBase {
		virtual void InternalOnInit() override
		{
#pragma region 创建 SquareShader
			// 创建 Shader
			m_squareShader = Shader::CreateShader("assets/shaders/triangle.glsl");

			// 创建 VertexArray
			m_squareVertexArray = VertexArray::CreateVertexArray();

			// 创建 VertexBuffer
			float squareVertices[4 * 5] = {
				 1.0f,  1.0f, 0.0f,			1.0f, 1.0f, // top right
				 1.0f, -1.0f, 0.0f,			1.0f, 0.0f, // bottom right
				-1.0f, -1.0f, 0.0f,			0.0f, 0.0f, // bottom left
				-1.0f,  1.0f, 0.0f,			0.0f, 1.0f  // top left 
			};
			SharedPtr<VertexBuffer> squareVertexBuffer = VertexBuffer::CreateVertexBuffer(squareVertices, sizeof(squareVertices));
			squareVertexBuffer->SetLayout({
				{EnShaderDataType::Float3, "a_Position"},
				{EnShaderDataType::Float2, "a_TexCoord"},
				});

			// 将 VertexBuffer 添加到 VertexArray 中
			m_squareVertexArray->AddVertexBuffer(squareVertexBuffer);

			// 创建 IndexBuffer
			uint32_t squareIndices[2 * 3] = {
				0, 1, 3,
				1, 2, 3
			};
			SharedPtr<IndexBuffer> squareIndexBuffer = IndexBuffer::CreateIndexBuffer(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

			// 设置 IndexBuffer 添加到 VertexArray 中
			m_squareVertexArray->SetIndexBuffer(squareIndexBuffer);
#pragma endregion

			// 创建 ComputeShader
			m_computeShader = Shader::CreateShader("assets/shaders/compute.glsl");

			int tex_w = 1280, tex_h = 960;
			m_outputTex = Texture2D::Create(tex_w, tex_h, EnInternalFormat::RGBA32F, EnDataFormat::RGBA);

			glBindImageTexture(0, m_outputTex->GetRendererID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
		}

		virtual void InternalOnUpdate() override
		{
			RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0 });
			RendererCommand::Clear();

			m_computeShader->Bind();
			
			glDispatchCompute(m_outputTex->GetWidth(), m_outputTex->GetHeight(), 1);

			// make sure writing to image has finished before read
			glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

			{ // normal drawing pass
				glClear(GL_COLOR_BUFFER_BIT);

				m_squareShader->Bind();
				m_outputTex->Bind();
				m_squareVertexArray->Bind();
				RendererSys::Draw(m_squareVertexArray);
			}
			
		}

		virtual void InternalOnClose() override
		{

		}
	private:
		SharedPtr<Shader> m_squareShader;
		SharedPtr<VertexArray> m_squareVertexArray;

		SharedPtr<Shader> m_computeShader;

		SharedPtr<Texture2D> m_outputTex;

		GLuint tex_output;
	};

	class Sandbox : public Application {
	public:
		Sandbox() {
			SetApplicationWorkFlow(new SandboxWorkFlow());
		}
	};

	UniquePtr<Application> CreateApplication() {
		return CreateUniqueByPtr(new Sandbox());
	}
}
