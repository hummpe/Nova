#include "novapch.h"
#include "Application.h"

#include "Nova/Events/ApplicationEvent.h"
#include "Nova/Log.h"

#include <GLFW/glfw3.h>

namespace Nova
{

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			// Magenta
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}
