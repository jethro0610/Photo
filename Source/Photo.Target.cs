using UnrealBuildTool;
using System.Collections.Generic;

public class PhotoTarget : TargetRules
{
	public PhotoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Photo" } );
	}
}
