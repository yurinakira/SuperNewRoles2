//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "ChatHandler.h"
#include "../TranslateDate.h"
#include "../LateTask.h"
#include "../Roles/Assassin.h"
#include "../Main.h"
#include "TitleMenuPatch.h"
#include "../CustomOption/CustomOptionDate.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../Helpers/CachedPlayer.h"
#include "../CustomRPC/CustomRPCSender.h"
#include "../ModHelpers.h"

using namespace BepInEx::IL2CPP::Utils;
using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

	void AmongUsClientOnPlayerJoinedPatch::Postfix(PlayerPhysics *__instance, LobbyBehaviour *lobby)
	{
		if (AmongUsClient::Instance->AmHost && AmongUsClient::Instance->GameMode != GameModes::FreePlay)
		{
			std::wstring text = ModTranslation::getString(L"WelcomeMessage1") + L"\n" + ModTranslation::getString(L"WelcomeMessage2") + L"\n" + ModTranslation::getString(L"WelcomeMessage3") + L"\n" + ModTranslation::getString(L"WelcomeMessage4") + L"\n" + ModTranslation::getString(L"WelcomeMessage5") + L"\n" + ModTranslation::getString(L"WelcomeMessage6") + L"\n" + ModTranslation::getString(L"WelcomeMessage7") + L"\n" + ModTranslation::getString(L"WelcomeMessage8") + L" " + L"\n.";
			new LateTask([&] ()
			{
				if (__instance->myPlayer.IsPlayer())
				{
					AddChatPatch::SendCommand(__instance->myPlayer, text, AddChatPatch::WelcomeToSuperNewRoles);
				}
			}, 1.0f);
			return;
		}
	}

std::wstring AddChatPatch::SNR = L"<color=#ffa500>Super</color><color=#ff0000>New</color><color=#00ff00>Roles</color>";
std::wstring AddChatPatch::SNRCommander = L"<size=200%>" + SNR + L"</size>";
std::wstring AddChatPatch::WelcomeToSuperNewRoles = L"<size=150%>Welcome To " + SNR + L"</size>";

	bool AddChatPatch::Prefix(PlayerControl *sourcePlayer, const std::wstring &chatText)
	{
		if (AmongUsClient::Instance->GameState == InnerNet::InnerNetClient::GameStates::Started)
		{
			if (AmongUsClient::Instance->AmHost)
			{
				Assassin::AddChat(sourcePlayer, chatText);
			}
		}

		auto Commands = chatText.Split(L" ");
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Equals' reference is not converted:
		if (Commands[0].Equals(L"/version", StringComparison::OrdinalIgnoreCase) || Commands[0].Equals(L"/v", StringComparison::OrdinalIgnoreCase))
		{
			std::wstring betatext = L"";
			if (SuperNewRolesPlugin::isBeta())
			{
				betatext = L"\nベータ版です！バグには注意してください！";
			}
			SendCommand(sourcePlayer, L" SuperNewRoles v" + SuperNewRolesPlugin::VersionString + L"\nCreate by ykundesu" + betatext);
			return false;
		}
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Equals' reference is not converted:
		else if (Commands[0].Equals(L"/Commands", StringComparison::OrdinalIgnoreCase) || Commands[0].Equals(L"/Cmd", StringComparison::OrdinalIgnoreCase))
		{
			std::wstring text = ModTranslation::getString(L"CommandsMessage0") + L"\n\n" + ModTranslation::getString(L"CommandsMessage1") + L"\n" + ModTranslation::getString(L"CommandsMessage2") + L"\n" + ModTranslation::getString(L"CommandsMessage3") + L"\n" + ModTranslation::getString(L"CommandsMessage4") + L"\n" + ModTranslation::getString(L"CommandsMessage5") + L"\n" + ModTranslation::getString(L"CommandsMessage6") + L"\n" + ModTranslation::getString(L"CommandsMessage7") + L"\n" + ModTranslation::getString(L"CommandsMessage8") + L"\n" + ModTranslation::getString(L"CommandsMessage9");
			SendCommand(sourcePlayer, text);
			return false;
		}
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Equals' reference is not converted:
		else if (Commands[0].Equals(L"/Discord", StringComparison::OrdinalIgnoreCase) || Commands[0].Equals(L"/dc", StringComparison::OrdinalIgnoreCase))
		{
			SendCommand(sourcePlayer, ModTranslation::getString(L"SNROfficialDiscordMessage") + L"\n" + MainMenuPatch::snrdiscordserver);
			return false;
		}
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Equals' reference is not converted:
		else if (Commands[0].Equals(L"/Twitter", StringComparison::OrdinalIgnoreCase) || Commands[0].Equals(L"/tw", StringComparison::OrdinalIgnoreCase))
		{
			SendCommand(sourcePlayer, ModTranslation::getString(L"SNROfficialTwitterMessage") + L"\n\n" + ModTranslation::getString(L"TwitterOfficialLink") + L"\n" + ModTranslation::getString(L"TwitterDevLink"));
			return false;
		}
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Equals' reference is not converted:
		else if (Commands[0].Equals(L"/GetInRoles", StringComparison::OrdinalIgnoreCase) || Commands[0].Equals(L"/gr", StringComparison::OrdinalIgnoreCase))
		{
			if (Commands.size() == 1)
			{
				if (sourcePlayer->AmOwner)
				{
					GetInRoleCommand(nullptr);
				}
				else
				{
					GetInRoleCommand(sourcePlayer);
				}
			}
			else
			{
				PlayerControl *target = sourcePlayer->AmOwner ? nullptr : sourcePlayer;
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Equals' reference is not converted:
				if (Commands.size() >= 2 && (Commands[1].Equals(L"mp", StringComparison::OrdinalIgnoreCase) || Commands[1].Equals(L"myplayer", StringComparison::OrdinalIgnoreCase) || Commands[1].Equals(L"myp", StringComparison::OrdinalIgnoreCase)))
				{
					target = sourcePlayer;
				}
				GetInRoleCommand(target);
			}
			return false;
		}
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Equals' reference is not converted:
		else if (Commands[0].Equals(L"/AllRoles", StringComparison::OrdinalIgnoreCase) || Commands[0].Equals(L"/ar", StringComparison::OrdinalIgnoreCase))
		{
			if (Commands.size() == 1)
			{
				if (sourcePlayer->AmOwner)
				{
					RoleCommand(nullptr);
				}
				else
				{
					RoleCommand(sourcePlayer);
				}
			}
			else
			{
				PlayerControl *target = sourcePlayer->AmOwner ? nullptr : sourcePlayer;
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Equals' reference is not converted:
				if (Commands.size() >= 3 && (Commands[2].Equals(L"mp", StringComparison::OrdinalIgnoreCase) || Commands[2].Equals(L"myplayer", StringComparison::OrdinalIgnoreCase) || Commands[2].Equals(L"myp", StringComparison::OrdinalIgnoreCase)))
				{
					target = sourcePlayer;
				}
				float sendtime;
				if (!float::TryParse(Commands[1], sendtime))
				{
					return false;
				}
				RoleCommand(target, sendtime);
			}
			return false;
		}
		else
		{
			return true;
		}
	}

	std::wstring AddChatPatch::GetChildText(std::vector<CustomOption::CustomOption*> &options, const std::wstring &indent)
	{
		std::wstring text = L"";
		for (auto option : options)
		{
			text += indent + option->getName() + L":" + option->getString() + L"\n";
			if (option->children.size() > 0)
			{
				text += GetChildText(option->children, indent + L"  ");
			}
		}
		return text;
	}

	std::wstring AddChatPatch::GetOptionText(CustomRoleOption *RoleOption, IntroDate *intro)
	{
		std::wstring text = L"";
		text += GetChildText(RoleOption->children, L"  ");
		return text;
	}

	std::wstring AddChatPatch::GetTeamText(TeamRoleType type)
	{
		std::wstring tempVar11;
		switch (type)
		{
			case TeamRoleType::Crewmate:
				tempVar11 = ModTranslation::getString(L"CrewMateName");
				break;
			case TeamRoleType::Impostor:
				tempVar11 = ModTranslation::getString(L"ImpostorName");
				break;
			case TeamRoleType::Neutral:
				tempVar11 = StringHelper::replace(ModTranslation::getString(L"NeutralName"), L"陣営", L"");
				break;
			default:
				tempVar11 = L"";
				break;
		}
		return tempVar11;
	}

	std::wstring AddChatPatch::GetText(CustomRoleOption *option)
	{
		std::wstring text = L"\n";
		IntroDate *intro = option->getIntro();
		text += GetTeamText(intro->Team) + ModTranslation::getString(L"Team") + L"\n";

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
