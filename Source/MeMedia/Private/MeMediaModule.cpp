// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MeMediaPCH.h"
#include "IMeMediaModule.h"
#include "MeMediaPlayer.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "mf")
#pragma comment(lib, "mfplat")
#pragma comment(lib, "uuid")


DEFINE_LOG_CATEGORY(LogMeMedia);

#define LOCTEXT_NAMESPACE "FMeMediaModule"


/**
 * Implements the MeMedia module.
 */
class FMeMediaModule
	: public IMeMediaModule
{
public:

	/** Default constructor. */
	FMeMediaModule()
		: Initialized(false)
	{ }

public:

	//~ IMeMediaModule interface

	virtual TSharedPtr<IMediaPlayer> CreatePlayer() override
	{
#if (WINVER >= _WIN32_WINNT_WIN8)
		if (Initialized)
		{
			return MakeShareable(new FMeMediaPlayer());
		}
#endif

		return nullptr;
	}

public:

	//~ IModuleInterface interface

	virtual void StartupModule() override
	{
#if (WINVER < _WIN32_WINNT_WIN8)
		UE_LOG(LogMeMedia, Log, TEXT("The MeMedia plug-in must be compiled on Windows 8 or later"));

		return;
#endif

		if (!LoadRequiredLibraries())
		{
			UE_LOG(LogMeMedia, Log, TEXT("Failed to load required Windows Media Engine libraries"));

			return;
		}

		// initialize Windows Media Engine
		HRESULT Result = MFStartup(MF_VERSION);

		if (FAILED(Result))
		{
			UE_LOG(LogMeMedia, Log, TEXT("Failed to initialize Windows Media Engine, Error %i"), Result);

			return;
		}

		Initialized = true;
	}

	virtual void ShutdownModule() override
	{
		if (Initialized)
		{
			// shutdown Windows Media Foundation
			MFShutdown();

			Initialized = false;
		}
	}

protected:

	/**
	 * Loads all required Windows libraries.
	 *
	 * @return true on success, false otherwise.
	 */
	bool LoadRequiredLibraries()
	{
		if (LoadLibraryW(TEXT("d3d11.dll")) == nullptr)
		{
			UE_LOG(LogMeMedia, Log, TEXT("Failed to load d3d11.dll"));

			return false;
		}

		if (LoadLibraryW(TEXT("mf.dll")) == nullptr)
		{
			UE_LOG(LogMeMedia, Log, TEXT("Failed to load mf.dll"));

			return false;
		}

		if (LoadLibraryW(TEXT("mfplat.dll")) == nullptr)
		{
			UE_LOG(LogMeMedia, Log, TEXT("Failed to load mfplat.dll"));

			return false;
		}

		return true;
	}

private:

	/** Whether the module has been initialized. */
	bool Initialized;

	/** The collection of supported media file types. */
	TArray<FString> SupportedFileExtensions;

	/** The collection of supported URI schemes. */
	TArray<FString> SupportedUriSchemes;
};


IMPLEMENT_MODULE(FMeMediaModule, MeMedia);


#undef LOCTEXT_NAMESPACE
