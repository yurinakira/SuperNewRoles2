#include "Main.h"
#include "obj/Debug/netstandard2.1/ThisAssembly.h"
#include "TranslateDate.h"
#include "ChacheManager/main.h"
#include "CustomCosmetics/CustomColors.h"
#include "Config.h"
#include "CustomOption/CustomOptionDate.h"
#include "Patch/FreeNamePatch.h"
#include "SubmergedCompatibility.h"
#include "LateTask.h"

using namespace BepInEx;
using namespace BepInEx::IL2CPP;
using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles
{

const std::wstring SuperNewRolesPlugin::Id = L"jp.ykundesu.supernewroles";
const std::wstring SuperNewRolesPlugin::VersionString = L"1.4.1.5";

	bool SuperNewRolesPlugin::isBeta()
	{
		return ThisAssembly::Git::Branch != L"master";
	}

System::Version *SuperNewRolesPlugin::Version = System::Version::Parse(VersionString);
BepInEx::Logging::ManualLogSource *SuperNewRolesPlugin::Logger;
Sprite *SuperNewRolesPlugin::ModStamp;
int SuperNewRolesPlugin::optionsPage = 1;

	Harmony *SuperNewRolesPlugin::getHarmony() const
	{
		return Harmony;
	}

SuperNewRolesPlugin *SuperNewRolesPlugin::Instance;
std::unordered_map<std::wstring, std::unordered_map<int, std::wstring>> SuperNewRolesPlugin::StringDATE;
bool SuperNewRolesPlugin::IsUpdate = false;
std::wstring SuperNewRolesPlugin::NewVersion = L"";
std::wstring SuperNewRolesPlugin::thisname;

	void SuperNewRolesPlugin::Load()
	{
		Logger = Log;
		Instance = this;
		// All Load() Start
		ModTranslation::Load();
		ChacheManager::Load();
		CustomCosmetics::CustomColors::Load();
		ConfigRoles::Load();
		CustomOption::CustomOptions::Load();
		Patches::FreeNamePatch::Initialize();
		// All Load() End

		// Old Delete Start

		try
		{
			DirectoryInfo *d = new DirectoryInfo(FileSystem::getDirectoryName(Application->dataPath) + LR"(\BepInEx\plugins)");
			std::vector<std::wstring> files = d->GetFiles(L"*.dll.old").Select([&] (std::any x)
			{
				x->FullName;
			})->ToArray(); // Getting old versions
			for (auto f : files)
			{
				File::Delete(f);
			}

			delete d;
		}
		catch (const std::runtime_error &e)
		{
			std::wcout << L"Exception occured when clearing old versions:\n" << e << std::endl;
		}

		// Old Delete End

		Logger->LogInfo(ModTranslation::getString(L"StartLogText"));

		auto assembly = Assembly::GetExecutingAssembly();

		StringDATE = std::unordered_map<std::wstring, std::unordered_map<int, std::wstring>>();
		getHarmony()->PatchAll();
		SubmergedCompatibility::Initialize();
	}

	void SuperNewRolesPlugin::AmBannedPatch::Postfix(bool &__result)
	{
		__result = false;
	}

	void SuperNewRolesPlugin::ChatControllerAwakePatch::Prefix()
	{
		SaveManager->chatModeType = 1;
		SaveManager->isGuest = false;
	}

	void SuperNewRolesPlugin::ChatControllerAwakePatch::Postfix(ChatController *__instance)
	{
		SaveManager->chatModeType = 1;
		SaveManager->isGuest = false;

		if (Input->GetKeyDown(KeyCode::F1))
		{
			if (!__instance->isActiveAndEnabled)
			{
				return;
			}
			__instance->Toggle();
		}
		else if (Input->GetKeyDown(KeyCode::F2))
		{
			__instance->SetVisible(false);
			new LateTask([&] ()
			{
				__instance->SetVisible(true);
			}, 0.0f, L"AntiChatBag");
		}
		if (__instance->IsOpen)
		{
			if (__instance->animating)
			{
				__instance->BanButton.MenuButton->enabled = false;
			}
			else
			{
				__instance->BanButton.MenuButton->enabled = true;
			}
		}
	}
}
