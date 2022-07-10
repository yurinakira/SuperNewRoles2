#include "FixedUpdate.h"
#include "../ModeHandler.h"
#include "../../Helpers/FastDestroyableSingleton.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../Roles/RoleHelper.h"
#include "../SuperHostRoles/main.h"
#include "main.h"
#include "ZombieOptions.h"
#include "../../TranslateDate.h"
#include "../../Helpers/RPCHelper.h"
#include "../../ModHelpers.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Zombie
{

float FixedUpdate::NameChangeTimer = 0;
bool FixedUpdate::IsStart = false;

	void FixedUpdate::TimerUpdate::Postfix(HudManager *__instance)
	{
		if (!(AmongUsClient::Instance->GameState == AmongUsClient::GameStates::Started))
		{
			return;
		}
		Mode::ModeHandler::HudUpdate(__instance);
		if (IsStart && NameChangeTimer != -10 && AmongUsClient::Instance->AmHost && ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Zombie}) && !FastDestroyableSingleton<HudManager*>::getInstance().IsIntroDisplayed)
		{
			if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Zombie}) && IsStart && NameChangeTimer != -10 && AmongUsClient::Instance->AmHost && AmongUsClient::Instance->GameState == AmongUsClient::GameStates::Started && !FastDestroyableSingleton<HudManager*>::getInstance().IsIntroDisplayed)
			{
				if (NameChangeTimer >= 0.0f)
				{
					NameChangeTimer -= Time::deltaTime;
				}
				else if (NameChangeTimer != -10)
				{
					for (auto p : CachedPlayer::AllPlayers)
					{
						p->RpcSetName(L"　");
						if (SuperNewRoles::RoleHelpers::isImpostor(p))
						{
							main::SetZombie(p);
						}
					}
					unsigned char BlueIndex = 1;
					for (auto p : CachedPlayer::AllPlayers)
					{
						if (!SuperNewRoles::Mode::Zombie::main::IsZombie(p))
						{
							/*
							p.UncheckSetVisor("visor_EmptyVisor");
							*/
							p->RpcSetColor(BlueIndex);
							/*
							p.RpcSetHat("hat_police");
	
							p.RpcSetSkin("skin_Police");
							*/
							ZombieOptions::ChengeSetting(p);
						}
					}
					NameChangeTimer = -10;
				}
			}
		}
	}

int FixedUpdate::FixedUpdateTimer = 0;

	void FixedUpdate::Update()
	{
		if (!IsStart || !AmongUsClient::Instance->AmHost)
		{
			return;
		}
		FixedUpdateTimer--;
		if (FixedUpdateTimer <= 0)
		{
			FixedUpdateTimer = 15;
			if (NameChangeTimer >= 0.0f)
			{
				for (auto p : CachedPlayer::AllPlayers)
				{
					SuperNewRoles::Helpers::RPCHelper::RpcSetNamePrivate(p, std::wstring::Format(ModTranslation::getString(L"ZombieTimerText"), static_cast<int>(NameChangeTimer) + 1));
				}
			}
			else
			{
				for (auto pint : main::ZombiePlayers)
				{
					auto p1 = ModHelpers::playerById(static_cast<unsigned char>(pint));
					for (auto p : CachedPlayer::AllPlayers)
					{
						if (!SuperNewRoles::Mode::Zombie::main::IsZombie(p))
						{
							if (p != nullptr && SuperNewRoles::RoleHelpers::isAlive(p) && !p->Data->Disconnected)
							{
								auto DistanceData = Vector2::Distance(p->transform.position, p1->transform.position);
								if (DistanceData <= 0.5f)
								{
									main::SetZombie(p);
								}
							}
						}
					}
				}
			}
		}
	}
}
