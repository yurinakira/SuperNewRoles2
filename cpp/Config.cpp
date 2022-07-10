//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "Config.h"
#include "Main.h"
#include "Intro/IntroPatch.h"
#include "Patch/CustomServer.h"

using namespace BepInEx::Configuration;
using namespace SuperNewRoles::Patches;

namespace SuperNewRoles
{

ConfigEntry<std::wstring> *ConfigRoles::Ip;
ConfigEntry<unsigned short> *ConfigRoles::Port;
ConfigEntry<bool> *ConfigRoles::StreamerMode;
ConfigEntry<bool> *ConfigRoles::AutoUpdate;
ConfigEntry<bool> *ConfigRoles::AutoCopyGameCode;
ConfigEntry<bool> *ConfigRoles::DebugMode;
ConfigEntry<bool> *ConfigRoles::CustomProcessDown;
ConfigEntry<bool> *ConfigRoles::IsVersionErrorView;
ConfigEntry<bool> *ConfigRoles::IsShareCosmetics;
ConfigEntry<std::wstring> *ConfigRoles::ShareCosmeticsNamePlatesURL;
ConfigEntry<bool> *ConfigRoles::IsAutoRoomCreate;
ConfigEntry<bool> *ConfigRoles::HideTaskArrows;
ConfigEntry<bool> *ConfigRoles::EnableHorseMode;
ConfigEntry<bool> *ConfigRoles::DownloadSuperNewNamePlates;
ConfigEntry<bool> *ConfigRoles::DownloadOtherSkins;
ConfigEntry<bool> *ConfigRoles::IsUpdate;

	ConfigEntry<std::wstring> *ConfigRoles::getIp()
	{
		return Ip;
	}

	void ConfigRoles::setIp(ConfigEntry<std::wstring> *value)
	{
		Ip = value;
	}

	ConfigEntry<unsigned short> *ConfigRoles::getPort()
	{
		return Port;
	}

	void ConfigRoles::setPort(ConfigEntry<unsigned short> *value)
	{
		Port = value;
	}

	ConfigEntry<bool> *ConfigRoles::getStreamerMode()
	{
		return StreamerMode;
	}

	void ConfigRoles::setStreamerMode(ConfigEntry<bool> *value)
	{
		StreamerMode = value;
	}

	ConfigEntry<bool> *ConfigRoles::getAutoUpdate()
	{
		return AutoUpdate;
	}

	void ConfigRoles::setAutoUpdate(ConfigEntry<bool> *value)
	{
		AutoUpdate = value;
	}

	ConfigEntry<bool> *ConfigRoles::getAutoCopyGameCode()
	{
		return AutoCopyGameCode;
	}

	void ConfigRoles::setAutoCopyGameCode(ConfigEntry<bool> *value)
	{
		AutoCopyGameCode = value;
	}

	ConfigEntry<bool> *ConfigRoles::getDebugMode()
	{
		return DebugMode;
	}

	void ConfigRoles::setDebugMode(ConfigEntry<bool> *value)
	{
		DebugMode = value;
	}

	ConfigEntry<bool> *ConfigRoles::getCustomProcessDown()
	{
		return CustomProcessDown;
	}

	void ConfigRoles::setCustomProcessDown(ConfigEntry<bool> *value)
	{
		CustomProcessDown = value;
	}

	ConfigEntry<bool> *ConfigRoles::isVersionErrorView()
	{
		return IsVersionErrorView;
	}

	void ConfigRoles::setVersionErrorView(ConfigEntry<bool> *value)
	{
		IsVersionErrorView = value;
	}

	ConfigEntry<bool> *ConfigRoles::isShareCosmetics()
	{
		return IsShareCosmetics;
	}

	void ConfigRoles::setShareCosmetics(ConfigEntry<bool> *value)
	{
		IsShareCosmetics = value;
	}

	ConfigEntry<std::wstring> *ConfigRoles::getShareCosmeticsNamePlatesURL()
	{
		return ShareCosmeticsNamePlatesURL;
	}

	void ConfigRoles::setShareCosmeticsNamePlatesURL(ConfigEntry<std::wstring> *value)
	{
		ShareCosmeticsNamePlatesURL = value;
	}

	ConfigEntry<bool> *ConfigRoles::isAutoRoomCreate()
	{
		return IsAutoRoomCreate;
	}

	void ConfigRoles::setAutoRoomCreate(ConfigEntry<bool> *value)
	{
		IsAutoRoomCreate = value;
	}

	ConfigEntry<bool> *ConfigRoles::getHideTaskArrows()
	{
		return HideTaskArrows;
	}

	void ConfigRoles::setHideTaskArrows(ConfigEntry<bool> *value)
	{
		HideTaskArrows = value;
	}

	ConfigEntry<bool> *ConfigRoles::getEnableHorseMode()
	{
		return EnableHorseMode;
	}

	void ConfigRoles::setEnableHorseMode(ConfigEntry<bool> *value)
	{
		EnableHorseMode = value;
	}

	ConfigEntry<bool> *ConfigRoles::getDownloadSuperNewNamePlates()
	{
		return DownloadSuperNewNamePlates;
	}

	void ConfigRoles::setDownloadSuperNewNamePlates(ConfigEntry<bool> *value)
	{
		DownloadSuperNewNamePlates = value;
	}

	ConfigEntry<bool> *ConfigRoles::getDownloadOtherSkins()
	{
		return DownloadOtherSkins;
	}

	void ConfigRoles::setDownloadOtherSkins(ConfigEntry<bool> *value)
	{
		DownloadOtherSkins = value;
	}

	ConfigEntry<bool> *ConfigRoles::isUpdate()
	{
		return IsUpdate;
	}

	void ConfigRoles::setUpdate(ConfigEntry<bool> *value)
	{
		IsUpdate = value;
	}

bool ConfigRoles::IsUpdated = false;

	void ConfigRoles::Load()
	{
		setStreamerMode(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"Enable Streamer Mode", false));
		setAutoUpdate(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"Auto Update", true));
		setDebugMode(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"Debug Mode", false));
		setAutoCopyGameCode(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"Auto Copy Game Code", true));
		setCustomProcessDown(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"CustomProcessDown", false));
		setVersionErrorView(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"IsVersionErrorView", true));
		setHideTaskArrows(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"HideTaskArrows", false));
		setShareCosmeticsNamePlatesURL(SuperNewRolesPlugin::Instance->Config.Bind(L"ShareCosmetics", L"NamePlateURL", L""));
		setAutoRoomCreate(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"AutoRoomCreate", true));
		setEnableHorseMode(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"EnableHorseMode", false));
		setDownloadSuperNewNamePlates(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"DownloadSuperNewNamePlates", true));
		setIp(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"Custom Server IP", L"127.0.0.1"));
		setPort(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"Custom Server Port", static_cast<unsigned short>(22023)));
		setUpdate(SuperNewRolesPlugin::Instance->Config.Bind(L"Custom", L"IsUpdate", true));
		if (isUpdate()->Value)
		{

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
