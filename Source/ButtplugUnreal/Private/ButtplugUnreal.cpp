// Copyright Epic Games, Inc. All Rights Reserved.

#include "ButtplugUnreal.h"

#define LOCTEXT_NAMESPACE "FButtplugUnrealModule"

void FButtplugUnrealModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FButtplugUnrealModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FButtplugUnrealModule, ButtplugUnreal)