// Sandbox module for Nova
#include <Nova.h>

class Nebula : public Nova::Application
{
public:
	Nebula()
	{

	}

	~Nebula()
	{

	}
};

Nova::Application* Nova::CreateApplication()
{
	return new Nebula();
}