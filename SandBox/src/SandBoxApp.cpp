
#include <Reagent.h>

class Sandbox : public rg::Application 
{
public:
	Sandbox() 
	{
		rg::Log::Init();
		rg::Log::GetCoreLogger()->warn("Initialized Log!");
		rg::Log::GetClientLogger()->info("Hello");
		RG_CORE_ERROR("Oh nonooooo");
	}
	~Sandbox()
	{

	}
};

rg::Application* rg::CreateApplication()
{
	return new Sandbox();
}