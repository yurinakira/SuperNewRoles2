//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "IntroPatch.h"
#include "../Mode/ModeHandler.h"
#include "../Helpers/CachedPlayer.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Roles/Madmate.h"
#include "../Roles/RoleHelper.h"
#include "../Roles/JackalFriends.h"
#include "../Roles/IntroHandler.h"
#include "IntroDate.h"
#include "../Mode/HideAndSeek/Intro.h"
#include "../TranslateDate.h"
#include "../Roles/RoleClass.h"
#include "../PlayerControlHepler.h"
#include "../LateTask.h"
#include "../Patch/HorseModePatch.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::HideAndSeek;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace TMPro;
using namespace UnityEngine;

namespace SuperNewRoles::Patches
{

	void IntroPatch::setupIntroTeamIcons(IntroCutscene *__instance, Il2CppSystem::Collections::Generic::List<PlayerControl*> *&yourTeam)
	{
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			auto newTeam2 = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
			newTeam2->Add(PlayerControl::LocalPlayer);
			yourTeam = newTeam2;
			if (PlayerControl::LocalPlayer::isCrew())
			{
				auto newTeam = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
				newTeam->Add(PlayerControl::LocalPlayer);
				for (auto p : CachedPlayer::AllPlayers)
				{
					if (p->PlayerId != CachedPlayer::LocalPlayer->PlayerId)
					{
						newTeam->Add(p);
					}
				}
				yourTeam = newTeam;

//C# TO C++ CONVERTER TODO TASK: A 'delete newTeam' statement was not added since newTeam was assigned to a parameter. Handle memory management manually.
			}
			else
			{
				switch (PlayerControl::LocalPlayer::getRole())
				{
					case RoleId::MadMate:
					case RoleId::MadMayor:
					case RoleId::MadJester:
					case RoleId::MadSeer:
					case RoleId::BlackCat:
					{
						if (Madmate::CheckImpostor(PlayerControl::LocalPlayer))
						{
							break;
						}
						ImpostorIntroTeam:
						Il2CppSystem::Collections::Generic::List<PlayerControl*> *ImpostorTeams = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
						ImpostorTeams->Add(PlayerControl::LocalPlayer);
						for (auto player : CachedPlayer::AllPlayers)
						{
							if ((SuperNewRoles::RoleHelpers::isImpostor(player) || SuperNewRoles::RoleHelpers::isRole(player, RoleId::Spy)) && player->PlayerId != CachedPlayer::LocalPlayer->PlayerId)
							{
								ImpostorTeams->Add(player);
							}
						}
						yourTeam = ImpostorTeams;
						break;

//C# TO C++ CONVERTER TODO TASK: A 'delete ImpostorTeams' statement was not added since ImpostorTeams was assigned to a parameter. Handle memory management manually.
					}
					case RoleId::SeerFriends:
					case RoleId::MayorFriends:
					case RoleId::JackalFriends:
					{
						if (JackalFriends::CheckJackal(PlayerControl::LocalPlayer))
						{
							break;
						}
						JackalIntroTeam:
						Il2CppSystem::Collections::Generic::List<PlayerControl*> *JackalTeams = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
						JackalTeams->Add(PlayerControl::LocalPlayer);
						for (auto player : CachedPlayer::AllPlayers)
						{
							if (SuperNewRoles::RoleHelpers::IsJackalTeamJackal(player) && player->PlayerId != CachedPlayer::LocalPlayer->PlayerId)
							{
								JackalTeams->Add(player);
							}
						}
						yourTeam = JackalTeams;
						break;

//C# TO C++ CONVERTER TODO TASK: A 'delete JackalTeams' statement was not added since JackalTeams was assigned to a parameter. Handle memory management manually.
					}
					case RoleId::Fox:
					{
						Il2CppSystem::Collections::Generic::List<PlayerControl*> *FoxTeams = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
						int FoxNum = 0;
						for (auto player : CachedPlayer::AllPlayers)
						{
							if (SuperNewRoles::RoleHelpers::isRole(player, CustomRPC::RoleId::Fox))
							{
								FoxNum++;
								FoxTeams->Add(player);
							}
						}
						yourTeam = FoxTeams;
						break;

//C# TO C++ CONVERTER TODO TASK: A 'delete FoxTeams' statement was not added since FoxTeams was assigned to a parameter. Handle memory management manually.
					}
					default:
						if (PlayerControl::LocalPlayer::isImpostor())
						{
							goto ImpostorIntroTeam;
						}
						else if (PlayerControl::LocalPlayer::IsJackalTeamJackal())
						{
							goto JackalIntroTeam;
						}
						break;
				}
			}

//C# TO C++ CONVERTER TODO TASK: A 'delete newTeam2' statement was not added since newTeam2 was assigned to a parameter. Handle memory management manually.
		}
		else
		{
			auto temp = ModeHandler::TeamHandler(__instance);
			Il2CppSystem::Collections::Generic->List<PlayerControl*> tempVar();
			if (temp != &tempVar)
			{
				yourTeam = temp;
			}
			else
			{
				temp = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
				temp->Add(PlayerControl::LocalPlayer);
				yourTeam = temp;
			}
		}
	}

	void IntroPatch::setupIntroTeam(IntroCutscene *__instance, Il2CppSystem::Collections::Generic::List<PlayerControl*> *&yourTeam)
	{
		IntroHandler::Handler();
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default, ModeId::SuperHostRoles}))
		{
			if (PlayerControl::LocalPlayer::isNeutral())
			{
				IntroDate *Intro = IntroDate::GetIntroDate(PlayerControl::LocalPlayer::getRole());
				__instance->BackgroundBar.material->color = Intro->color;
				__instance->TeamTitle->text = ModTranslation::getString(Intro->NameKey + L"Name");
				__instance->TeamTitle->color = Intro->color;
				__instance->ImpostorText->text = L"";
			}
			else
			{
				switch (PlayerControl::LocalPlayer::getRole())
				{
					case RoleId::MadMate:
					case RoleId::MadJester:
					case RoleId::MadStuntMan:
					case RoleId::MadMayor:
					case RoleId::SeerFriends:
					case RoleId::MayorFriends:
					{
						IntroDate *Intro = IntroDate::GetIntroDate(PlayerControl::LocalPlayer::getRole());
						__instance->BackgroundBar.material->color = Intro->color;
						__instance->TeamTitle->text = ModTranslation::getString(Intro->NameKey + L"Name");
						__instance->TeamTitle->color = Intro->color;
						__instance->ImpostorText->text = L"";
						break;
					}
				}
			}
		}

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
