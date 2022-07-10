#include "CoEnterVent.h"
#include "../ModeHandler.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../../Roles/RoleClass.h"
#include "../../Roles/RoleHelper.h"
#include "../../LateTask.h"

using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{

	bool CoEnterVent::Prefix(PlayerPhysics *__instance, int id)
	{
		if (!AmongUsClient::Instance->AmHost || !ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			return true;
		}
		RoleId role = __instance->myPlayer.getRole();
		switch (role)
		{
			case RoleId::Minimalist:
				if (RoleClass::Minimalist::UseVent)
				{
					return true;
				}
				break;
			case RoleId::Egoist:
				if (RoleClass::Egoist::UseVent)
				{
					return true;
				}
				break;
			case RoleId::Demon:
				if (RoleClass::Demon::IsUseVent)
				{
					return true;
				}
				break;
			case RoleId::Arsonist:
				if (RoleClass::Arsonist::IsUseVent)
				{
					return true;
				}
				break;
			case RoleId::Jackal:
				if (RoleClass::Jackal::IsUseVent)
				{
					return true;
				}
				break;
			case RoleId::MadMaker:
				if (RoleClass::MadMaker::IsUseVent)
				{
					return true;
				}
				break;
			case RoleId::Technician:
				if (RoleHelpers::IsSabotage())
				{
					return true;
				}
				break;
			case RoleId::Samurai:
				if (RoleClass::Samurai::UseVent)
				{
					return true;
				}
				break;
			case RoleId::RemoteSheriff:
			case RoleId::Sheriff:
			case RoleId::truelover:
			case RoleId::FalseCharges:
				break;
			default:
				return true;
		}
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(__instance->NetId, static_cast<unsigned char>(RpcCalls::BootFromVent), SendOption::Reliable, -1);
		writer->WritePacked(127);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		new LateTask([&] ()
		{
			int clientId = __instance->myPlayer.getClientId();
			MessageWriter *writer2 = AmongUsClient::Instance->StartRpcImmediately(__instance->NetId, static_cast<unsigned char>(RpcCalls::BootFromVent), SendOption::Reliable, clientId);
			writer2->Write(id);
			AmongUsClient::Instance->FinishRpcImmediately(writer2);
		}, 0.5f, L"Anti Vent");
		return false;
	}
}
