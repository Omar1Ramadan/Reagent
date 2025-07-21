#pragma once
#include <stdio.h>
// API for use of Reagent Applications 

#include "Reagent/Application.h"

// entry point for reagent to run
#ifdef RG_ENTRY
	#include "Reagent/EntryPoint.h"
#endif

//logger for reagent systems
#include "Reagent/Log.h"

// precompiled header file for Reagent
#include "rgpch.h"

// assertions for reagent systems
#include "Reagent/Core/Assert.h"