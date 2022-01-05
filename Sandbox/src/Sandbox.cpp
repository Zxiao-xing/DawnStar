#pragma once

#include <DawnStar.h>
#include <Core/EntryPoint.h>
#include <glad/glad.h>
#include <glm/glm/glm.hpp>

namespace DawnStar {

	class SandboxWorkFlow : public ApplicationWorkFlowBase {
		virtual void InternalOnInit() override
		{
			
			m_triangleShader = Shader::CreateShader("assets/shaders/triangle.glsl");
			
            float vertices[] = {
				 1.0f,  1.0f, 0.0f,			1.0f, 1.0f, // top right
				 1.0f, -1.0f, 0.0f,			1.0f, 0.0f, // bottom right
				-1.0f, -1.0f, 0.0f,			0.0f, 0.0f, // bottom left
				-1.0f,  1.0f, 0.0f,			0.0f, 1.0f  // top left 
            };
            unsigned int indices[] = {  // note that we start from 0!
                0, 1, 3,  // first Triangle
                1, 2, 3   // second Triangle
            };
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindVertexArray(0);

			m_computeShader = Shader::CreateShader("assets/shaders/compute.glsl");

			int tex_w = 1280, tex_h = 960;
			m_outputTex = Texture2D::Create(tex_w, tex_h, EnInternalFormat::RGBA32F, EnDataFormat::RGBA);

			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_outputTex->GetWidth(), m_outputTex->GetHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
			glBindImageTexture(0, m_outputTex->GetRendererID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

			// 总工作组最大数量
			int work_grp_cnt[3];

			glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
			glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
			glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);

			printf("max global (total) work group counts x:%i y:%i z:%i\n",
				work_grp_cnt[0], work_grp_cnt[1], work_grp_cnt[2]);

			// 本地工作组最大数量
			int work_grp_size[3];

			glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
			glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
			glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);

			printf("max local (in one shader) work group sizes x:%i y:%i z:%i\n",
				work_grp_size[0], work_grp_size[1], work_grp_size[2]);

			int work_grp_inv;
			// 本地工作组的最大工作组单元数
			glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);
			printf("max local work group invocations %i\n", work_grp_inv);
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

				m_triangleShader->Bind();
				m_outputTex->Bind();
				glBindVertexArray(VAO);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
			
		}

		virtual void InternalOnClose() override
		{

		}
	private:
		SharedPtr<Shader> m_triangleShader;
		SharedPtr<Shader> m_computeShader;

		SharedPtr<Texture2D> m_outputTex;


		GLuint tex_output;
		unsigned int VBO, VAO, EBO;
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
