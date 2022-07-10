#include "Bestfalsecharge.h"
#include "RoleClass.h"
#include "../CustomRPC/CustomRPC.h"

using namespace HarmonyLib;
using namespace Hazel;

namespace SuperNewRoles::Roles
{

	void Bestfalsecharge::MeetingEnd::Prefix(MeetingHud *__instance)
	{
		if (AmongUsClient::Instance->AmHost && !RoleClass::Bestfalsecharge::IsOnMeeting)
		{
			for (auto p : RoleClass::Bestfalsecharge::BestfalsechargePlayer)
			{
				MessageWriter *RPCWriter = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ExiledRPC), Hazel::SendOption::Reliable, -1);
				RPCWriter->Write(p->PlayerId);
				AmongUsClient::Instance->FinishRpcImmediately(RPCWriter);
				CustomRPC::RPCProcedure::ExiledRPC(p->PlayerId);
			}
			RoleClass::Bestfalsecharge::IsOnMeeting = true;
		}
	}
}
