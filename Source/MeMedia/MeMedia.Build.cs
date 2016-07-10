// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class MeMedia : ModuleRules
	{
		public MeMedia(TargetInfo Target)
		{
            DynamicallyLoadedModuleNames.AddRange(
                new string[] {
                    "Media",
				}
            );

			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Core",
                    "RenderCore",
				}
			);

			PrivateIncludePathModuleNames.AddRange(
				new string[] {
                    "Media",
				}
			);

			PrivateIncludePaths.AddRange(
				new string[] {
					"MeMedia/Private",
                    "MeMedia/Private/Player",
				}
			);

            if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
            {
                PublicDelayLoadDLLs.Add("d3d11.dll");
                PublicDelayLoadDLLs.Add("mf.dll");
                PublicDelayLoadDLLs.Add("mfplat.dll");
                PublicDelayLoadDLLs.Add("uuid.dll");
            }

			if (Target.Platform == UnrealTargetPlatform.XboxOne)
			{
				PublicAdditionalLibraries.Add("mfplat.lib");
				PublicAdditionalLibraries.Add("mfuuid.lib");
			}
		}
	}
}
