using UnrealBuildTool;

public class KeshUE4FundamentalTypeWrapperPlugin : ModuleRules
{
    public KeshUE4FundamentalTypeWrapperPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
    }
}
