#pragma once

#include "AutoUpdate.h"
#include <string>

using namespace BepInEx::Configuration;
using namespace SuperNewRoles::Patches;
namespace SuperNewRoles
{
	class ConfigRoles final
	{
	private:
		static ConfigEntry<std::wstring> *Ip;
		static ConfigEntry<unsigned short> *Port;
		static ConfigEntry<bool> *StreamerMode;
		static ConfigEntry<bool> *AutoUpdate;
		static ConfigEntry<bool> *AutoCopyGameCode;
		static ConfigEntry<bool> *DebugMode;
		static ConfigEntry<bool> *CustomProcessDown;
		static ConfigEntry<bool> *IsVersionErrorView;
		static ConfigEntry<bool> *IsShareCosmetics;
		static ConfigEntry<std::wstring> *ShareCosmeticsNamePlatesURL;
		static ConfigEntry<bool> *IsAutoRoomCreate;
		static ConfigEntry<bool> *HideTaskArrows;
		static ConfigEntry<bool> *EnableHorseMode;
		static ConfigEntry<bool> *DownloadSuperNewNamePlates;
		static ConfigEntry<bool> *DownloadOtherSkins;
		static ConfigEntry<bool> *IsUpdate;

	public:
		static ConfigEntry<std::wstring> *getIp();
		static void setIp(ConfigEntry<std::wstring> *value);
		static ConfigEntry<unsigned short> *getPort();
		static void setPort(ConfigEntry<unsigned short> *value);
		static ConfigEntry<bool> *getStreamerMode();
		static void setStreamerMode(ConfigEntry<bool> *value);
		static ConfigEntry<bool> *getAutoUpdate();
		static void setAutoUpdate(ConfigEntry<bool> *value);
		static ConfigEntry<bool> *getAutoCopyGameCode();
		static void setAutoCopyGameCode(ConfigEntry<bool> *value);
		static ConfigEntry<bool> *getDebugMode();
		static void setDebugMode(ConfigEntry<bool> *value);
		static ConfigEntry<bool> *getCustomProcessDown();
		static void setCustomProcessDown(ConfigEntry<bool> *value);
		static ConfigEntry<bool> *isVersionErrorView();
		static void setVersionErrorView(ConfigEntry<bool> *value);
		static ConfigEntry<bool> *isShareCosmetics();
		static void setShareCosmetics(ConfigEntry<bool> *value);
		static ConfigEntry<std::wstring> *getShareCosmeticsNamePlatesURL();
		static void setShareCosmeticsNamePlatesURL(ConfigEntry<std::wstring> *value);
		static ConfigEntry<bool> *isAutoRoomCreate();
		static void setAutoRoomCreate(ConfigEntry<bool> *value);
		static ConfigEntry<bool> *getHideTaskArrows();
		static void setHideTaskArrows(ConfigEntry<bool> *value);
		static ConfigEntry<bool> *getEnableHorseMode();
		static void setEnableHorseMode(ConfigEntry<bool> *value);
		static ConfigEntry<bool> *getDownloadSuperNewNamePlates();
		static void setDownloadSuperNewNamePlates(ConfigEntry<bool> *value);
		static ConfigEntry<bool> *getDownloadOtherSkins();
		static void setDownloadOtherSkins(ConfigEntry<bool> *value);
		static ConfigEntry<bool> *isUpdate();
		static void setUpdate(ConfigEntry<bool> *value);
		static bool IsUpdated;
		static void Load();
	};
}
