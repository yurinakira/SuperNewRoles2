#include "Nekomata.h"
#include "../../../CustomRPC/CustomRPC.h"
#include "../../../Helpers/CachedPlayer.h"
#include "../../../BotManager.h"
#include "../../../Roles/RoleHelper.h"
#include "../../../ModHelpers.h"
#include "../../../Patch/PlayerControlPatch.h"
#include "../../../Roles/RoleClass.h"
#include "Jester.h"

using namespace Hazel;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Patches;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{

	void Nekomata::WrapUp(GameData::PlayerInfo *exiled)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (exiled->Object.isRole(CustomRPC::RoleId::NiceNekomata) || exiled->Object.isRole(CustomRPC::RoleId::EvilNekomata) || exiled->Object.isRole(CustomRPC::RoleId::BlackCat))
		{
			NekomataEnd(exiled);
		}
	}

	void Nekomata::NekomataEnd(GameData::PlayerInfo *exiled)
	{
		std::vector<PlayerControl*> p;
		for (auto p1 : CachedPlayer::AllPlayers)
		{
			if (p1->Data->PlayerId != exiled->PlayerId && SuperNewRoles::RoleHelpers::isAlive(p1) && SuperNewRoles::BotManager::IsPlayer(p1))
			{
				p.push_back(p1);
			}
		}
		NekomataProc(p);
	}

	void Nekomata::NekomataProc(std::vector<PlayerControl*> &p)
	{
		auto rdm = ModHelpers::GetRandomIndex(p);
		auto random = p[rdm];
		SuperNewRoles::Patches::CheckMurderPatch::RpcCheckExile(random);
		if ((SuperNewRoles::RoleHelpers::isRole(random, CustomRPC::RoleId::NiceNekomata) || SuperNewRoles::RoleHelpers::isRole(random, CustomRPC::RoleId::EvilNekomata) || SuperNewRoles::RoleHelpers::isRole(random, CustomRPC::RoleId::BlackCat)) && RoleClass::NiceNekomata::IsChain)
		{
			p.erase(p.begin() + rdm);
			NekomataProc(p);
		}
		Jester::WrapUp(random->Data);
	}
}
