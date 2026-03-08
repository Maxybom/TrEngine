#include <TrEngine.h>

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public TrEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f), m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(TrEngine::VertexArray::Create());

		std::array<float, 3 * 7> vertices =
			{
				-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // red
				0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,	// green
				0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f	// blue
			};

		m_VertexBuffer.reset(TrEngine::VertexBuffer::Create(vertices.data(), sizeof(vertices)));

		TrEngine::BufferLayout layout =
			{
				{TrEngine::ShaderDataType::Float3, "a_Position"},
				{TrEngine::ShaderDataType::Float4, "a_Color"}};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		std::array<uint32_t, 3> indices = {0, 1, 2};
		m_IndexBuffer.reset(TrEngine::IndexBuffer::Create(indices.data(), sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_SquareVA.reset(TrEngine::VertexArray::Create());

		std::array<float, 3 * 4> squareVertices =
			{
				-0.5f, -0.5f, -0.1f,
				0.5f, -0.5f, -0.1f,
				0.5f, 0.5f, -0.1f,
				-0.5f, 0.5f, -0.1f};

		std::shared_ptr<TrEngine::VertexBuffer> SquareVB(TrEngine::VertexBuffer::Create(squareVertices.data(), sizeof(squareVertices)), [](TrEngine::VertexBuffer *ptr)
														 { delete ptr; });

		SquareVB->SetLayout({{TrEngine::ShaderDataType::Float3, "a_Position"}});
		m_SquareVA->AddVertexBuffer(SquareVB);

		std::array<uint32_t, 6> squareIndices = {0, 1, 2, 2, 3, 0};
		std::shared_ptr<TrEngine::IndexBuffer> squareIB(TrEngine::IndexBuffer::Create(squareIndices.data(), sizeof(squareIndices) / sizeof(uint32_t)), [](TrEngine::IndexBuffer *ptr)
														{ delete ptr; });

		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position =  u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;
		in vec4 v_Color;

		void main()
		{
			vec3 mixedColor = mix(v_Color.rgb, vec3(v_Position * 0.5 + 0.5), 0.5);
			color = vec4(mixedColor, v_Color.a);
		}

		)";

		m_Shader.reset(new TrEngine::Shader(vertexSource, fragmentSource));

		std::string vertexSource2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource2 = R"(
			#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;

		void main()
		{
			color = vec4(0.2, 0.3, 0.8, 1.0);
		}

		)";

		m_Shader2.reset(new TrEngine::Shader(vertexSource2, fragmentSource2));
	}

	void OnUpdate(TrEngine::Timestep timestep) override
	{

		TE_TRACE("Timestep: {0} seconds ({1} ms)", timestep.GetSeconds(), timestep.GetMilliseconds());

		if (TrEngine::Input::IsKeyPressed(TE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed * timestep;
		else if (TrEngine::Input::IsKeyPressed(TE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed * timestep;

		if (TrEngine::Input::IsKeyPressed(TE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed * timestep;
		else if (TrEngine::Input::IsKeyPressed(TE_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed * timestep;

		if (TrEngine::Input::IsKeyPressed(TE_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * timestep;
		else if (TrEngine::Input::IsKeyPressed(TE_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * timestep;

		// work for move only the square(outside the for cycle)
		// if (TrEngine::Input::IsKeyPressed(TE_KEY_J))
		// 	m_SquarePosition.x -= m_SqaureMoveSpeed * timestep;
		// else if (TrEngine::Input::IsKeyPressed(TE_KEY_L))
		// 	m_SquarePosition.x += m_SqaureMoveSpeed * timestep;

		// if (TrEngine::Input::IsKeyPressed(TE_KEY_I))
		// 	m_SquarePosition.y -= m_SqaureMoveSpeed * timestep;
		// else if (TrEngine::Input::IsKeyPressed(TE_KEY_K))
		// 	m_SquarePosition.y += m_SqaureMoveSpeed * timestep;

		TrEngine::Window &window = TrEngine::Application::Get().GetWindow();

		TrEngine::RenderCommand::SetViewport(0, 0, window.GetWidth(), window.GetHeight());

		TrEngine::RenderCommand::SetClearColor({0.2, 0.2, 0.2, 1});
		TrEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		TrEngine::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				glm::vec3 pos(x * 0.15f, y * 0.15f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				TrEngine::Renderer::Submit(m_Shader2, m_SquareVA, transform); // square
			}
		}

		TrEngine::Renderer::Submit(m_Shader, m_VertexArray); // triangle

		TrEngine::Renderer::EndScene();
	}

	void OnEvent(TrEngine::Event &event) override
	{
	}

private:
	std::shared_ptr<TrEngine::Shader> m_Shader;
	std::shared_ptr<TrEngine::VertexArray> m_VertexArray;
	std::shared_ptr<TrEngine::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<TrEngine::IndexBuffer> m_IndexBuffer;

	std::shared_ptr<TrEngine::Shader> m_Shader2;
	std::shared_ptr<TrEngine::VertexArray> m_SquareVA;

	TrEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 1.0f; // Units per second

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 90.0f; // Degrees per second

	glm::vec3 m_SquarePosition = {0.0f, 0.0f, 0.0f};

	float m_SqaureMoveSpeed = 2.0f; // Units per second
};

class Sandbox : public TrEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{
	}
};

TrEngine::Application *TrEngine::CreateApplication()
{
	return new Sandbox();
}