#include <TrEngine.h>

#include "imgui.h"

class ExampleLayer : public TrEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f)
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
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				-0.5f, 0.5f, 0.0f};

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

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position =  u_ViewProjection * vec4(a_Position, 1.0);
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

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

	void OnUpdate() override
	{

		if (TrEngine::Input::IsKeyPressed(TE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed;
		else if (TrEngine::Input::IsKeyPressed(TE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed;

		if (TrEngine::Input::IsKeyPressed(TE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed;
		else if (TrEngine::Input::IsKeyPressed(TE_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed;

		if (TrEngine::Input::IsKeyPressed(TE_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (TrEngine::Input::IsKeyPressed(TE_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed;

		TrEngine::Window &window = TrEngine::Application::Get().GetWindow();

		TrEngine::RenderCommand::SetViewport(0, 0, window.GetWidth(), window.GetHeight());

		TrEngine::RenderCommand::SetClearColor({0.2, 0.2, 0.2, 1});
		TrEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		TrEngine::Renderer::BeginScene(m_Camera);
		TrEngine::Renderer::Submit(m_Shader, m_VertexArray); // first this
		TrEngine::Renderer::Submit(m_Shader2, m_SquareVA);	 // second square

		TrEngine::Renderer::Submit(m_Shader2, m_VertexArray);

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
	float m_CameraSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 1.0f;
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