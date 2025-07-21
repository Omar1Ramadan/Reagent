
//#include <Reagent.h>
//#include <Reagent/EntryPoint.h>
#include "../../Reagent/src/Reagent.h"
#include "../../Reagent/src/Reagent/EntryPoint.h"

class Sandbox : public rg::Application 
{
public:
	Sandbox() 
	{}
	~Sandbox()
	{

	}
};

rg::Application* rg::CreateApplication()
{
	return new Sandbox();
}