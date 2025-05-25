#pragma once

// macro for defining api or macros to make writing simplier 
#ifdef RG_WINDOWS
	#ifdef RG_DLL
		#define RG_API __declspec(dllexport)	
	#else
		#define RG_API __declspec(dllimport)
	#endif
#else
	#error Reagent Only Supports Windows
#endif