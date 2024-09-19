// Copyright 2024 PubNub Inc. All Rights Reserved.

#include "PubnubChatSDK.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Kismet/KismetSystemLibrary.h"

#define LOCTEXT_NAMESPACE "FPubnubChatSDKModule"

void FPubnubChatSDKModule::StartupModule()
{

	FString BaseDir = IPluginManager::Get().FindPlugin("PubnubChat")->GetBaseDir();
	FString LibraryPath;
	
#if PLATFORM_WINDOWS

	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/sdk/lib/Win64/pubnub-chat.dll"));

#elif PLATFORM_MAC
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/sdk/lib/macos/libpubnub-chat.dylib"));

#endif
	
	ChatSDKLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (!ChatSDKLibraryHandle)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ChatSDKModuleHandle", "Failed to load pubnub third party library"));
	}
}

void FPubnubChatSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(ChatSDKLibraryHandle);
	ChatSDKLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPubnubChatSDKModule, PubnubChatSDK)
