// Sakurasaki All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class WeaverEditorTarget : TargetRules
{
	public WeaverEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Weaver" } );
	}
}
