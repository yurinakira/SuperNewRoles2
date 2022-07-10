#include "Tuna.h"
#include "RoleClass.h"
#include "../Mode/ModeHandler.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleHelper.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Tuna::Postfix()
	{
		if (AmongUsClient::Instance->GameState != InnerNet::InnerNetClient::GameStates::Started)
		{
			return;
		}
		if (RoleClass::IsMeeting)
		{
			return;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			if (PlayerControl::LocalPlayer::isAlive() && PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::Tuna) && RoleClass::Tuna::IsMeetingEnd)
			{
				if (RoleClass::Tuna::Position[CachedPlayer::LocalPlayer->PlayerId] == CachedPlayer::LocalPlayer->transform->position)
				{
					if (RoleClass::Tuna::Timer <= 0.1f)
					{
						CachedPlayer::LocalPlayer->PlayerControl->RpcMurderPlayer(CachedPlayer::LocalPlayer->PlayerControl);
					}
					RoleClass::Tuna::Timer -= Time::deltaTime;
				}
				else
				{
					RoleClass::Tuna::Timer = RoleClass::Tuna::StoppingTime;
					RoleClass::Tuna::Position[CachedPlayer::LocalPlayer->PlayerId] = CachedPlayer::LocalPlayer->transform->position;
				}
			}
		}
		else
		{
			for (auto p : RoleClass::Tuna::TunaPlayer)
			{
				if (SuperNewRoles::RoleHelpers::isAlive(p) && RoleClass::Tuna::IsMeetingEnd)
				{
					if (RoleClass::Tuna::Position[p->PlayerId] == p->transform.position)
					{
						RoleClass::Tuna::Timers[p->PlayerId] -= Time::deltaTime;
						if (RoleClass::Tuna::Timers[p->PlayerId] <= 0)
						{
							p->RpcMurderPlayer(p);
						}
					}
					else
					{
						RoleClass::Tuna::Timers[p->PlayerId] = RoleClass::Tuna::StoppingTime;
					}
					RoleClass::Tuna::Position[p->PlayerId] = p->transform.position;
				}
			}
		}
	}

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
	void Tuna::Prefix(MeetingHud *__instance)
	{
		RoleClass::Tuna::IsMeetingEnd = true;
	}
}
