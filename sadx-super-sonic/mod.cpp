#include "pch.h"

// Entry point of the mod

HelperFunctions HelperFunctionsGlobal;

Buttons TransformButton = Buttons_B;
bool EnableTransformationVoice = true;
bool EnableTikalUnusedVoice = true;
bool RemoveLimitations = false;
bool DetransformButton = true;
bool AlwaysSuperSonic = false;
bool ExtendedGamePlay = true;
bool CustomPhysics = true;
bool DisableAura = false;
bool ChangeMusic = true;
bool CustomAnims = true;

void ReadConfig(const char* path) {
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

	TransformButton = config->getInt("General", "TransformButton", 0) == 0 ? Buttons_B : Buttons_X;
	EnableTransformationVoice = config->getBool("Sounds", "EnableTransformationVoice", true);
	EnableTikalUnusedVoice = config->getBool("Sounds", "EnableTikalUnusedVoice", true);
	DetransformButton = config->getBool("General", "DetransformButton", true);
	AlwaysSuperSonic = config->getBool("General", "AlwaysSuperSonic", false);
	ExtendedGamePlay = config->getBool("General", "ExtendedGameplay", true);
	CustomPhysics = config->getBool("General", "CustomPhysics", true);
	DisableAura = config->getBool("General", "DisableAura", false);
	CustomAnims = config->getBool("General", "CustomAnims", true);
	ChangeMusic = config->getBool("Sounds", "ChangeMusic", true);
	
	if (AlwaysSuperSonic == true || config->getBool("General", "RemoveLimitations", false)) {
		RemoveLimitations = true;
	}

	delete config;
}

extern "C" {
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		HelperFunctionsGlobal = helperFunctions;

		ReadConfig(path);

		SuperSonic_Init(); // Main code to load Super Sonic
		Objects_Init(); // Edit external objects like SpinDash Trail, SuperPhysics...
		WaterHack_Init(); // Hack to allow the player to float on water when Super Sonic
		Animations_Init(); // Allow Sonic actions for Super Sonic
		Physics_Init(path);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}