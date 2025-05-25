
#include <Reagent.h>

class Sandbox : public rg::Application 
{
public:
	Sandbox() 
	{

	}
	~Sandbox()
	{

	}
};

rg::Application* rg::CreateApplication()
{
	return new Sandbox();
}