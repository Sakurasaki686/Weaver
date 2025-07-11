// Sakurasaki All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class WeaverTarget : TargetRules
{
	public WeaverTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Weaver" } );
	}
}
