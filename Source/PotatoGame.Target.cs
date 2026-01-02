// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PotatoGameTarget : TargetRules
{
	public PotatoGameTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V6;
        bOverrideBuildEnvironment = true;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
        ExtraModuleNames.Add("PotatoGame");
    }
}
