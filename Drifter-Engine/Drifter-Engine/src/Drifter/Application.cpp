#include "dfpch.h"

#include "Application.h"
#include <stdio.h>
#include "Log.h"

#include "glad/glad.h"

namespace Drifter {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Drifter::ShaderDataType::Float:    return GL_FLOAT;
		case Drifter::ShaderDataType::Float2:   return GL_FLOAT;
		case Drifter::ShaderDataType::Float3:   return GL_FLOAT;
		case Drifter::ShaderDataType::Float4:   return GL_FLOAT;
		case Drifter::ShaderDataType::Mat3:     return GL_FLOAT;
		case Drifter::ShaderDataType::Mat4:     return GL_FLOAT;
		case Drifter::ShaderDataType::Int:      return GL_INT;
		case Drifter::ShaderDataType::Int2:     return GL_INT;
		case Drifter::ShaderDataType::Int3:     return GL_INT;
		case Drifter::ShaderDataType::Int4:     return GL_INT;
		case Drifter::ShaderDataType::Bool:     return GL_BOOL;
		}

		DF_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application() {
		DF_CORE_ASSERT(!s_Instance, "Application instance already exists!");
		s_Instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		GenerateOpenGLBuffers();
		SetBufferData();

		const char* vert = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			out vec3 v_Position;			

			void main(){
				v_Position = a_Position;
				gl_Position = vec4(v_Position, 1.0);
			}
		)";

		const char* frag = R"(
			#version 330 core

			layout(location=0) out vec4 fragColor;
			in vec3 v_Position;
			
			void main(){
				vec3 col = vec3(1,1,1);
				float r = v_Position.x + .5;
				float g = 1 - r;
				float b = v_Position.y + .5;
				vec3 posCol = vec3(r,g,b);
				fragColor = vec4(col * posCol, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vert,frag));
	}



	Application::~Application() {

	}

	void Application::OnEvent(Event& e)
	{
		DF_LOG_TRACE("{0}", e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_layerStack.PopLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_layerStack.PopOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_running = false;
		return true;
	}

	void Application::GenerateOpenGLBuffers()
	{
		glGenVertexArrays(1, &m_vertexArray);
		glBindVertexArray(m_vertexArray);
	}

	void Application::SetBufferData()
	{
		const int VERT_SIZE = 3;
		const int POINT_COUNT = 3;
		GLfloat vertices[VERT_SIZE * POINT_COUNT] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"}
			};

			m_VertexBuffer.reset(
				VertexBuffer::Create(vertices, sizeof(vertices), layout));
		}
		const int TRI_COUNT = 1;
		GLuint indices[TRI_COUNT * 3] = {
			0, 1, 2
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		auto layout = m_VertexBuffer->GetLayout();
		int index = 0;
		for (auto& bufferElement : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				bufferElement.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(bufferElement.Type),
				bufferElement.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)bufferElement.Offset
			);
			index++;
		}
		
	}

	void Application::Run() {
		DF_LOG_INFO("Welcome to Drifter!");


		while (m_running) {
			m_window->OnFrameBegin();
			for (Layer* layer : m_layerStack) {
				layer->OnUpdate();
			}

			m_Shader->Bind();
			glBindVertexArray(m_vertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount() , GL_UNSIGNED_INT, 0);
			
			
			m_window->OnFrameEnd();
		}
	}
}