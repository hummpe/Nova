#include "novapch.h"

#include "WindowsWindow.h"

namespace Nova {

	static bool s_GLFWInitialized = false;

	// Implements the static Window* Create in Window base class
	Window* Window::Create(const WindowProperties& props)
	{
		return new WindowsWindow{ props };
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}


	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		NOVA_CORE_INFO("Creating window: {0} ({1} {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			NOVA_CORE_ASSERT(succes, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		// TODO: Add explaining comments to this section
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		// m_Data sends events "back from GLFW"
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		// Very basic implementation of VSync
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
