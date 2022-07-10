//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "ShareGameVersion.h"
#include "../Main.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Roles/RoleClass.h"
#include "../CustomOption/CustomOptionDate.h"
#include "../Config.h"
#include "../TranslateDate.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

	void PlayerCountChange::Prefix(GameStartManager *__instance)
	{
		__instance->MinPlayers = 1;
	}

bool ShareGameVersion::IsVersionOK = false;
bool ShareGameVersion::IsChangeVersion = false;
bool ShareGameVersion::IsRPCSend = false;
float ShareGameVersion::timer = 600;
float ShareGameVersion::RPCTimer = 1.0f;
bool ShareGameVersion::notcreateroom = false;

	void ShareGameVersion::AmongUsClientOnPlayerJoinedPatch::Postfix()
	{
		if (PlayerControl::LocalPlayer != nullptr)
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"[VersionShare]Version Shared!");
			MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ShareSNRVersion), Hazel::SendOption::Reliable, -1);
			writer->Write(static_cast<unsigned char>(SuperNewRolesPlugin::Version->Major));
			writer->Write(static_cast<unsigned char>(SuperNewRolesPlugin::Version->Minor));
			writer->Write(static_cast<unsigned char>(SuperNewRolesPlugin::Version->Build));
			writer->WritePacked(AmongUsClient::Instance->ClientId);
			writer->Write(static_cast<unsigned char>(SuperNewRolesPlugin::Version->Revision < 0 ? 0xFF : SuperNewRolesPlugin::Version->Revision));
			writer->Write(Assembly::GetExecutingAssembly()->ManifestModule->ModuleVersionId.ToByteArray());
			AmongUsClient::Instance->FinishRpcImmediately(writer);
			CustomRPC::RPCProcedure::ShareSNRversion(SuperNewRolesPlugin::Version->Major, SuperNewRolesPlugin::Version->Minor, SuperNewRolesPlugin::Version->Build, SuperNewRolesPlugin::Version->Revision, Assembly::GetExecutingAssembly()->ManifestModule->ModuleVersionId, AmongUsClient::Instance->ClientId);
		}
	}

	void ShareGameVersion::GameStartManagerStartPatch::Postfix()
	{
		timer = 600.0f;
		RPCTimer = 1.0f;
		notcreateroom = false;
		RoleClass::ClearAndReloadRoles();
		GameStartManagerUpdatePatch::Proce = 0;
		GameStartManagerUpdatePatch::LastBlockStart = false;
		GameStartManagerUpdatePatch::VersionPlayers = std::unordered_map<int, PlayerVersion*>();
	}

bool ShareGameVersion::GameStartManagerUpdatePatch::update = false;
std::unordered_map<int, PlayerVersion*> ShareGameVersion::GameStartManagerUpdatePatch::VersionPlayers;
int ShareGameVersion::GameStartManagerUpdatePatch::Proce = 0;
std::wstring ShareGameVersion::GameStartManagerUpdatePatch::currentText = L"";
bool ShareGameVersion::GameStartManagerUpdatePatch::LastBlockStart = false;

	void ShareGameVersion::GameStartManagerUpdatePatch::Prefix(GameStartManager *__instance)
	{
		if (!GameData::Instance)
		{
			return; // Not host or no instance
		}
		update = GameData::Instance->PlayerCount != __instance->LastPlayerCount;
	}

	void ShareGameVersion::GameStartManagerUpdatePatch::Postfix(GameStartManager *__instance)
	{
		Proce++;
		if (Proce >= 10)
		{

			MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ShareSNRVersion), Hazel::SendOption::Reliable, -1);
			writer->Write(static_cast<unsigned char>(SuperNewRolesPlugin::Version->Major));
			writer->Write(static_cast<unsigned char>(SuperNewRolesPlugin::Version->Minor));
			writer->Write(static_cast<unsigned char>(SuperNewRolesPlugin::Version->Build));
			writer->WritePacked(AmongUsClient::Instance->ClientId);
			writer->Write(static_cast<unsigned char>(SuperNewRolesPlugin::Version->Revision < 0 ? 0xFF : SuperNewRolesPlugin::Version->Revision));
			writer->Write(Assembly::GetExecutingAssembly()->ManifestModule->ModuleVersionId.ToByteArray());
			AmongUsClient::Instance->FinishRpcImmediately(writer);
			CustomRPC::RPCProcedure::ShareSNRversion(SuperNewRolesPlugin::Version->Major, SuperNewRolesPlugin::Version->Minor, SuperNewRolesPlugin::Version->Build, SuperNewRolesPlugin::Version->Revision, Assembly::GetExecutingAssembly()->ManifestModule->ModuleVersionId, AmongUsClient::Instance->ClientId);
			Proce = 0;
		}
		std::wstring message = L"";
		bool blockStart = false;
		if (AmongUsClient::Instance->AmHost)
		{
			if (CustomOptions::DisconnectNotPCOption->getBool())
			{
				for (InnerNet::ClientData *p : AmongUsClient::Instance->allClients.GetFastEnumerator())
				{
					Platforms::StandaloneEpicPC *and_Keyword = dynamic_cast<Platforms::StandaloneEpicPC*>(p->PlatformData.Platform);
					if (and_Keyword == nullptr not_Keyword Platforms::StandaloneSteamPC)
					{
						AmongUsClient::Instance->KickPlayer(p->Id, false);
					}
				}
			}
		}
		if (ConfigRoles::isVersionErrorView()->Value)
		{
			if (!AmongUsClient::Instance->AmHost)
			{
				if (VersionPlayers.find(AmongUsClient::Instance->HostId) == VersionPlayers.end())
				{
					message += L"\n" + ModTranslation::getString(L"ErrorHostNoVersion") + L"\n";
					blockStart = true;
				}
				else
				{
					auto client = AmongUsClient::Instance->GetHost();
					PlayerVersion *PV = VersionPlayers[client->Id];
					int diff = SuperNewRolesPlugin::Version->CompareTo(PV->version);
					if (diff > 0)
					{
						message += StringHelper::formatSimple(L"{0} (v{1})\n", ModTranslation::getString(L"ErrorHostChangeVersion"), VersionPlayers[client->Id]->version);
						blockStart = true;
					}
					else if (diff < 0)
					{
						message += StringHelper::formatSimple(L"{0} (v{1})\n", ModTranslation::getString(L"ErrorHostChangeVersion"), VersionPlayers[client->Id]->version);
						blockStart = true;
					}
					else if (!PV->GuidMatches())
					{ // version presumably matches, check if Guid matches
						message += StringHelper::formatSimple(L"{0} (v{1})\n", ModTranslation::getString(L"ErrorHostChangeVersion"), VersionPlayers[client->Id]->version);
						blockStart = true;
					}
				}
			}
			for (auto client : AmongUsClient::Instance->allClients.GetFastEnumerator()->ToArray())
			{
				if (client->Id != AmongUsClient::Instance->HostId)
				{
					if (VersionPlayers.find(client->Id) == VersionPlayers.end())
					{
						if (!(client->PlatformData.Platform != Platforms::StandaloneEpicPC && client->PlatformData.Platform != Platforms::StandaloneSteamPC && CustomOptions::DisconnectNotPCOption->getBool()))
						{
							message += std::wstring::Format(ModTranslation::getString(L"ErrorClientNoVersion"), client->PlayerName) + L"\n";
							blockStart = true;
						}
					}
					else
					{
						PlayerVersion *PV = VersionPlayers[client->Id];
						int diff = SuperNewRolesPlugin::Version->CompareTo(PV->version);
						if (diff > 0)
						{
							message += StringHelper::formatSimple(L"{0} (v{1})\n", std::wstring::Format(ModTranslation::getString(L"ErrorClientChangeVersion"), client->Character.Data->PlayerName), VersionPlayers[client->Id]->version);
							blockStart = true;
						}
						else if (diff < 0)
						{
							message += StringHelper::formatSimple(L"{0} (v{1})\n", std::wstring::Format(ModTranslation::getString(L"ErrorClientChangeVersion"), client->Character.Data->PlayerName), VersionPlayers[client->Id]->version);
							blockStart = true;
						}
						else if (!PV->GuidMatches())

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
