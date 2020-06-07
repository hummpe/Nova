#pragma once

#ifdef NOVA_PLATFORM_WINDOWS

extern Nova::Application* Nova::CreateApplication();

int main(int argc, char** argv)
{
	// TODO: Move this from EntryPoint to another "System Init-place"
	Nova::Log::Init();
	NOVA_CORE_SET_LOG_LEVEL(Nova::LOG_LEVEL::TRACE);
	NOVA_CORE_INFO("Initalized Core Logger!");
	NOVA_INFO("Initalized Client Logger!");

	auto app = Nova::CreateApplication();
	NOVA_INFO("Initalized App!");
	app->Run();
	delete app;
}

#endif