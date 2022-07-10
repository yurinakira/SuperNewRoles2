#include "LadderDead.h"
#include "../Mode/ModeHandler.h"
#include "../Helpers/CachedPlayer.h"
#include "../ModHelpers.h"
#include "../Roles/RoleHelper.h"
#include "../LateTask.h"
#include "../CustomOption/CustomOptionDate.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Roles;
using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

	void LadderDead::Reset()
	{
		TargetLadderData = std::unordered_map<unsigned char, Vector3*>();
	}

	void LadderDead::FixedUpdate()
	{
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			if (PlayerControl::LocalPlayer::isDead())
			{
				return;
			}
			if (TargetLadderData.find(CachedPlayer::LocalPlayer->PlayerId) != TargetLadderData.end())
			{
				if (Vector2::Distance(TargetLadderData[CachedPlayer::LocalPlayer->PlayerId], CachedPlayer::LocalPlayer->transform->position) < 0.5f)
				{
					if (PlayerControl::LocalPlayer::moveable)
					{
						PlayerControl::LocalPlayer::RpcMurderPlayer(PlayerControl::LocalPlayer);
					}
				}
			}
		}
		else
		{
			if (AmongUsClient::Instance->AmHost)
			{
				for (auto data : TargetLadderData)
				{
					PlayerControl *player = ModHelpers::playerById(data->Key);
					if (SuperNewRoles::RoleHelpers::isDead(player))
					{
						continue;
					}
					if (Vector2::Distance(data->Value, player->transform.position) < 0.5f)
					{
						player->Data->IsDead = true;
						new LateTask([&] ()
						{
							player->RpcMurderPlayer(player);
						}, 0.05f);
					}
				}
			}
		}
	}

std::unordered_map<unsigned char, Vector3*> LadderDead::TargetLadderData;

	void LadderDead::ladder::Postfix(PlayerPhysics *__instance, Ladder *source, unsigned char climbLadderSid)
	{
		auto sourcepos = source->transform.position;
		auto targetpos = source->Destination->transform.position;
		//降りている
		if (sourcepos->y > targetpos->y)
		{
			//SuperNewRolesPlugin.Logger.LogInfo("降りています");
			int Chance = UnityEngine::Random::Range(1, 10);
			//SuperNewRolesPlugin.Logger.LogInfo(aaa);
			//SuperNewRolesPlugin.Logger.LogInfo(100 - kakuritu);
			if (Chance <= (CustomOptions::LadderDeadChance->getSelection() + 1))
			{
				TargetLadderData[__instance->myPlayer.PlayerId] = targetpos;
			}
		}
	}
}
