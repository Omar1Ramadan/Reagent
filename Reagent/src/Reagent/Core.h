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

#define BIT(x) (1 << x)

namespace rg{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}