using UnrealBuildTool;
using System.Collections.Generic;

public class PhotoEditorTarget : TargetRules
{
	public PhotoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Photo" } );
	}
}
