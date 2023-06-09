#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/LayerStack.h"


namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance;}
		inline Window& GetWindow() { return *m_Window;}
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Runing = true;
		LayerStack m_layerStack;
	private:
		static Application* s_Instance;

	};

	Application* CreateApplication();
}

