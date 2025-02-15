#include "Tepch.h"

#include "Application.h"
#include "TrEngine/Log.h"

#include "TrEngine/Event/ApplicationEvent.h"
#include "Input.h"

namespace TrEngine
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case TrEngine::ShaderDataType::Float:	return GL_FLOAT;
			case TrEngine::ShaderDataType::Float2:	return GL_FLOAT;
			case TrEngine::ShaderDataType::Float3:	return GL_FLOAT;
			case TrEngine::ShaderDataType::Float4:	return GL_FLOAT;
			case TrEngine::ShaderDataType::Mat3:	return GL_FLOAT;
			case TrEngine::ShaderDataType::Mat4:	return GL_FLOAT;
			case TrEngine::ShaderDataType::Int:	    return GL_INT;
			case TrEngine::ShaderDataType::Int2:	return GL_INT;
			case TrEngine::ShaderDataType::Int3:	return GL_INT;
			case TrEngine::ShaderDataType::Int4:	return GL_INT;
			case TrEngine::ShaderDataType::Bool:	return GL_BOOL;
		}

		TE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application()
	{
		TE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		std::array<float, 3 * 7> vertices =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // red
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // green
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f  // Blue
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices.data(), sizeof(vertices)));
		{
			BufferLayout layout =
			{
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
			};

			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				m_VertexBuffer->GetLayout().GetStride(), (const void*) element.Offset);
			index++;
		}

		std::array<uint32_t, 3> indices = {0, 1, 2};
		m_IndexBuffer.reset(IndexBuffer::Create(indices.data(), sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 0) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{ 
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;
		in vec4 v_Color;

		void main()
		{
			// Mescola il colore del vertice con una componente basata sulla posizione
			vec3 mixedColor = mix(v_Color.rgb, vec3(v_Position * 0.5 + 0.5), 0.5);
			color = vec4(mixedColor, v_Color.a);
		}

		)";

		m_Shader.reset(new Shader(vertexSource, fragmentSource));
	}

	Application::~Application() = default;

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
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
			glClearColor(0.2, 0.2, 0.2, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			auto [x, y] = Input::GetMousePosition();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}