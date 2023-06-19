#include "hzpch.h"
#include "Application.h"

#include "glad/glad.h"



namespace Hazel{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance£¬ "Application already exist!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		unsigned int id;
		glGenVertexArrays(1, &id);
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		HZ_CORE_TRACE("{0}", e);

		for (auto it = m_layerStack.end(); it!=m_layerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::Run()
	{
		
		while (m_Runing)
		{
			for (auto layer : m_layerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();

		}
	}

	bool Application::OnWindowClose(WindowCloseEvent & e)
	{
		m_Runing = false;
		return true;
	}
}