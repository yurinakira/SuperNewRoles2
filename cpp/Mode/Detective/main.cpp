#include "main.h"
#include "DetectiveOptions.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../Roles/RoleHelper.h"
#include "../../ModHelpers.h"
#include "../../Helpers/RPCHelper.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../SuperHostRoles/FixedUpdate.h"

using namespace Hazel;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Detective
{

bool main::IsNotDetectiveWin = false;
bool main::IsNotDetectiveVote = false;
bool main::IsDetectiveNotTask = false;
bool main::IsNotDetectiveMeetingButton = false;
PlayerControl *main::DetectivePlayer;
Color32 *main::DetectiveColor = new Color32(255, 0, 255, std::numeric_limits<unsigned char>::max());

	void main::ClearAndReload()
	{
		IsNotDetectiveWin = DetectiveOptions::IsWinNotCheckDetective->getBool();
		IsNotDetectiveVote = DetectiveOptions::IsNotDetectiveVote->getBool();
		IsDetectiveNotTask = DetectiveOptions::DetectiveIsNotTask->getBool();
		IsNotDetectiveMeetingButton = DetectiveOptions::IsNotDetectiveMeetingButton->getBool();
	}

	void main::RoleSelect()
	{
		DetectivePlayer = PlayerControl::LocalPlayer;
		std::vector<PlayerControl*> selectplayers;
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::RoleHelpers::isCrew(p))
			{
				selectplayers.push_back(p);
			}
		}
		auto random = ModHelpers::GetRandom(selectplayers);
		MessageWriter *writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::SetDetective);
		writer->Write(random->PlayerId);
		SuperNewRoles::Helpers::RPCHelper::EndRPC(writer);
		CustomRPC::RPCProcedure::SetDetective(random->PlayerId);
		DetectivePlayer->RpcSetName(ModHelpers::cs(DetectiveColor, SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(DetectivePlayer)));
		DetectivePlayer->SetName(ModHelpers::cs(DetectiveColor, SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(DetectivePlayer)));
	}

	void main::MurderPatch(PlayerControl *target)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		/*
		if (target.PlayerId != 0)
		{
		    foreach (PlayerControl p in CachedPlayer.AllPlayers)
		    {
		        if (!p.Data.Disconnected && p.isImpostor())
		        {
		            p.RpcSetNamePrivate(ModHelpers.cs(RoleClass.ImpostorRed, p.getDefaultName()), target);
		        }
		    }
		} else
		{
		    foreach (PlayerControl p in CachedPlayer.AllPlayers)
		    {
		        if (!p.Data.Disconnected && p.isImpostor())
		        {
		            p.SetName(ModHelpers.cs(RoleClass.ImpostorRed, p.getDefaultName()));
		        }
		    }
		}
		*/
	}
}
