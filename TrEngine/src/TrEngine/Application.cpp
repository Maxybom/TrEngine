#include "Tepch.h"

#include "Application.h"
#include "TrEngine/Log.h"

#include "TrEngine/Event/ApplicationEvent.h"
#include "Input.h"

#include "Trengine/Renderer/Renderer.h"

namespace TrEngine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application *Application::s_Instance = nullptr;

	Application::Application()
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		TE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_VertexArray.reset(VertexArray::Create());

		std::array<float, 3 * 7> vertices =
			{
				-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // red
				0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,	// green
				0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f	// blue
			};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices.data(), sizeof(vertices)));

		BufferLayout layout =
			{
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"}};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		std::array<uint32_t, 3> indices = {0, 1, 2};
		m_IndexBuffer.reset(IndexBuffer::Create(indices.data(), sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_SquareVA.reset(VertexArray::Create());

		std::array<float, 3 * 4> squareVertices =
			{
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				-0.5f, 0.5f, 0.0f};

		std::shared_ptr<VertexBuffer> SquareVB(VertexBuffer::Create(squareVertices.data(), sizeof(squareVertices)), [](VertexBuffer *ptr)
											   { delete ptr; });

		SquareVB->SetLayout({{ShaderDataType::Float3, "a_Position"}});
		m_SquareVA->AddVertexBuffer(SquareVB);

		std::array<uint32_t, 6> squareIndices = {0, 1, 2, 2, 3, 0};
		std::shared_ptr<IndexBuffer> squareIB(IndexBuffer::Create(squareIndices.data(), sizeof(squareIndices) / sizeof(uint32_t)), [](IndexBuffer *ptr)
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

		m_Shader.reset(new Shader(vertexSource, fragmentSource));

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

		m_Shader2.reset(new Shader(vertexSource2, fragmentSource2));
	}

	Application::~Application() = default;

	void Application::PushLayer(Layer *layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer *layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		if (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard)
		{
			e.SetHandled(true);
			return;
		}

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

			RenderCommand::SetClearColor({0.2, 0.2, 0.2, 1});
			RenderCommand::Clear();

			m_Camera.SetRotation(45.0f);

			Renderer::BeginScene(m_Camera);
			Renderer::Submit(m_Shader2, m_VertexArray);
			Renderer::Submit(m_Shader, m_VertexArray);
			Renderer::EndScene();

			for (Layer *layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();

			for (Layer *layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent &e)
	{
		m_Running = false;
		return true;
	}
}