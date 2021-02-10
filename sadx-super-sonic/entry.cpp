#include "pch.h"

void SuperSonic_Init(const HelperFunctions& helperFunctions, const IniFile* config);
void Objects_Init(const IniFile* config, const IniFile* physics);
void WaterHack_Init(const IniFile* config);
void GamePlay_Init(const IniFile* config);
void SuperSonic_InitAnimTable();

static bool Initialized = false;

HelperFunctions HelperFunctionsGlobal;

extern "C" {
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions) {
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		const IniFile* physics = new IniFile(std::string(path) + "\\physics.ini");

		HelperFunctionsGlobal = helperFunctions;

		SuperSonic_Init(helperFunctions, config); // Main code to load Super Sonic
		Objects_Init(config, physics); // Edit external objects like SpinDash Trail, SuperPhysics...
		WaterHack_Init(config); // Hack to allow the player to float on water when Super Sonic
		GamePlay_Init(config); // Allow Sonic actions for Super Sonic

		delete config;
		delete physics;
	}

	__declspec(dllexport) void __cdecl OnFrame() {
		if (Initialized == false && SonicAnimData->Animation->motion != nullptr) {
			SuperSonic_InitAnimTable();
			Initialized = true;
		}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}