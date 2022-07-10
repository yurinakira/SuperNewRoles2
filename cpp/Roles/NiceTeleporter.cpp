#include "NiceTeleporter.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleHelper.h"
#include "../ModHelpers.h"
#include "../CustomRPC/CustomRPC.h"

using namespace Hazel;
using namespace SuperNewRoles::Buttons;

namespace SuperNewRoles::Roles
{

	void NiceTeleporter::ResetCoolDown()
	{
		HudManagerStartPatch::TeleporterButton->MaxTimer = RoleClass::NiceTeleporter::CoolTime;
		RoleClass::NiceTeleporter::ButtonTimer = DateTime::Now;
	}

	void NiceTeleporter::TeleportStart()
	{
		std::vector<PlayerControl*> aliveplayers;
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p) && p->CanMove)
			{
				aliveplayers.push_back(p);
			}
		}
		auto player = ModHelpers::GetRandom<PlayerControl*>(aliveplayers);
		CustomRPC::RPCProcedure::TeleporterTP(player->PlayerId);

		MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::TeleporterTP), Hazel::SendOption::Reliable, -1);
		Writer->Write(player->PlayerId);
		AmongUsClient::Instance->FinishRpcImmediately(Writer);
	}

	bool NiceTeleporter::IsNiceTeleporter(PlayerControl *Player)
	{
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::NiceTeleporter::NiceTeleporterPlayer, Player))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void NiceTeleporter::EndMeeting()
	{
		HudManagerStartPatch::SheriffKillButton->MaxTimer = RoleClass::NiceTeleporter::CoolTime;
		RoleClass::NiceTeleporter::ButtonTimer = DateTime::Now;
	}
}
