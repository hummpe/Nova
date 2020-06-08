#include "Application.h"

#include "Nova/Events/ApplicationEvent.h"
#include "Nova/Log.h"

namespace Nova
{

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		// TODO: Test of WindowResizeEvent - Remove it
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			NOVA_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			NOVA_ERROR(e);
		}

		while (true);
	}

}
