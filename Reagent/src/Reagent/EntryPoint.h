#pragma once
// the entry point for the Sandbox Application

#ifdef RG_WINDOWS

// external return the createapplication function from the namespace
extern rg::Application* rg::CreateApplication();

int main(int argc, char** argv)
{
	printf("Starting From Reagent Entry Point\n");
	auto app = rg::CreateApplication();
	app->Run();
	delete app;
}
#endif 
