
using UnrealBuildTool;
using System.Collections.Generic;

public class SpartaProject_8EditorTarget : TargetRules
{
	public SpartaProject_8EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("SpartaProject_8");
	}
}
