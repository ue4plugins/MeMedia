// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Runtime/Core/Public/Core.h"
#include "Runtime/Core/Public/Async/Async.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Runtime/Media/Public/IMediaAudioSink.h"
#include "Runtime/Media/Public/IMediaModule.h"
#include "Runtime/Media/Public/IMediaStringSink.h"
#include "Runtime/Media/Public/IMediaPlayerFactory.h"
#include "Runtime/Media/Public/IMediaTextureSink.h"

#include "Runtime/Core/Public/Windows/AllowWindowsPlatformTypes.h"
#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <Mfmediaengine.h>
#include "Runtime/Core/Public/Windows/COMPointer.h"
#include "Runtime/Core/Public/Windows/HideWindowsPlatformTypes.h"


/** Log category for the MeMedia module. */
DECLARE_LOG_CATEGORY_EXTERN(LogMeMedia, Log, All);
