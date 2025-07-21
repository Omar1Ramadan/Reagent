#pragma once
#include "rgpch.h"
#include "Log.h"
// the entry point for the Sandbox Application

#ifdef RG_WINDOWS

// external return the createapplication function from the namespace
extern rg::Application* rg::CreateApplication();

int main(int argc, char** argv)
{

	// to be removed should have system for handling modules that are run into entry point
	rg::Log::Init();
	RG_CORE_WARN("from entry oops");

	printf("Starting From Reagent Entry Point\n");
	auto app = rg::CreateApplication();
	app->Run();
	delete app;
}
#endif 
