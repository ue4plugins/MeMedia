// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MeMediaEditorPCH.h"
#include "ModuleInterface.h"


/**
 * Implements the MeMediaEditor module.
 */
class FMeMediaEditorModule
	: public IModuleInterface
{
public:

	//~ IModuleInterface interface

	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};


IMPLEMENT_MODULE(FMeMediaEditorModule, MeMediaEditor);
