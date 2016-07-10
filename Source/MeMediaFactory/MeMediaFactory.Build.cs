// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class MeMediaFactory : ModuleRules
	{
		public MeMediaFactory(TargetInfo Target)
		{
            DynamicallyLoadedModuleNames.AddRange(
                new string[] {
                    "Media",
				}
            );

			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Core",
                    "CoreUObject",
                    "MediaAssets",
                }
			);

			PrivateIncludePathModuleNames.AddRange(
				new string[] {
                    "MeMedia",
				}
			);

			PrivateIncludePaths.AddRange(
				new string[] {
					"MeMediaFactory/Private",
				}
			);

			if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
			{
				DynamicallyLoadedModuleNames.Add("MeMedia");
			}
		}
	}
}
