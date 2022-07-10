#include "HandleGhostRole.h"
#include "../Mode/ModeHandler.h"
#include "../ModHelpers.h"
#include "RoleHelper.h"
#include "TeamRoleType.h"
#include "../Helpers/CachedPlayer.h"
#include "../AllRoleSetClass.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(RoleManager __instance, [HarmonyArgument(0)] PlayerControl player)
	bool HandleGhostRole::AssignRole::Prefix(RoleManager *__instance, PlayerControl *player)
	{
		if (!(ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}) || ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles})))
		{
			return true;
		}
		//生存者と割り当て済みの人は弾く
		if (SuperNewRoles::RoleHelpers::isAlive(player) || !SuperNewRoles::RoleHelpers::isGhostRole(player, RoleId::DefaultRole))
		{
			return false;
		}
		//幽霊役職がアサインされていたら守護天使をアサインしない
		return !HandleAssign(player);
	}

	bool HandleGhostRole::HandleAssign(PlayerControl *player)
	{
		//各役職にあったアサインをする
		auto Team = TeamRoleType::Error;
		if (SuperNewRoles::RoleHelpers::isCrew(player))
		{
			Team = TeamRoleType::Crewmate;
		}
		else if (SuperNewRoles::RoleHelpers::isNeutral(player))
		{
			Team = TeamRoleType::Neutral;
		}
		else
		{
			Team = TeamRoleType::Impostor;
		}
		std::vector<IntroDate*> GhostRoles;
		for (auto intro : IntroDate::GhostRoleDatas)
		{
			if (intro->Team != Team)
			{
				continue;
			}
			GhostRoles.push_back(intro);
		}
		auto assignrole = Assing(GhostRoles);
		if (assignrole == RoleId::DefaultRole)
		{
			return false;
		}
		switch (Team)
		{
			case TeamRoleType::Impostor:
				if (AllRoleSetClass::ImpostorGhostRolePlayerNum <= 0)
				{
					return false;
				}
				AllRoleSetClass::ImpostorGhostRolePlayerNum--;
				break;
			case TeamRoleType::Neutral:
				if (AllRoleSetClass::NeutralGhostRolePlayerNum <= 0)
				{
					return false;
				}
				AllRoleSetClass::NeutralGhostRolePlayerNum--;
				break;
			case TeamRoleType::Crewmate:
				if (AllRoleSetClass::CrewMateGhostRolePlayerNum <= 0)
				{
					return false;
				}
				AllRoleSetClass::CrewMateGhostRolePlayerNum--;
				break;

		}
		SuperNewRoles::RoleHelpers::setRoleRPC(player, assignrole);
		return true;
	}

	RoleId HandleGhostRole::Assing(std::vector<IntroDate*> &datas)
	{
		std::vector<RoleId> Assigns;
		std::vector<RoleId> Assignnos;
		ModeId mode = ModeHandler::GetMode();
		for (auto data : datas)
		{
			//その役職のプレイヤー数を取得
			auto count = AllRoleSetClass::GetPlayerCount(data->RoleId);
			//設定を取得
			auto option = IntroDate::GetOption(data->RoleId);
			//確率を取得
			auto selection = option->getSelection();

			//確率が0%ではないかつ、
			//もう割り当てきられてないか(最大人数まで割り当てられていないか)
			if ((option->isSHROn || mode != ModeId::SuperHostRoles) && selection != 0 && count > CachedPlayer::AllPlayers.ToArray()->size()([&] (CachedPlayer *pc)
			{
				SuperNewRoles::RoleHelpers::isGhostRole(pc->PlayerControl, data->RoleId);
			}))
			{
				//100%なら100%アサインListに入れる
				if (selection == 10)
				{
					Assigns.push_back(data->RoleId);
					//100%アサインリストの中身が0だったら処理しない(100%アサインリストのほうがアサインされるため)
				}
				else if (Assigns.size() <= 0)
				{
					//確率分だけRoleIdを入れる
					for (int i = 0; i < selection; i++)
					{
						Assignnos.push_back(data->RoleId);
					}
				}
			}
		}
		//100%アサインリストの中身が0ではなかったらランダムに選んでアサイン
		if (Assigns.size() > 0)
		{
			return ModHelpers::GetRandom(Assigns);
			//100%ではない、アサインリストの中身が0ではなかったらランダムに選んでアサイン
		}
		else if (Assignnos.size() > 0)
		{
			return ModHelpers::GetRandom(Assignnos);
		}
		//どっちも中身が0だったら通常の役職(DefaultRole)を返す
		return RoleId::DefaultRole;
	}
}
