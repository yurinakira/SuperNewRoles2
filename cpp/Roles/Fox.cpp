#include "Fox.h"
#include "../ModHelpers.h"
#include "EvilEraser.h"
#include "RoleClass.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Fox::setPlayerOutline(PlayerControl *target, Color *color)
	{
		if (target == nullptr || target->MyRend == nullptr)
		{
			return;
		}

		SuperNewRoles::ModHelpers::MyRend(target)->material.SetFloat(L"_Outline", 1.0f);
		SuperNewRoles::ModHelpers::MyRend(target)->material.SetColor(L"_OutlineColor", color);
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target)
	void Fox::FoxMurderPatch::Prefix(PlayerControl *__instance, PlayerControl *target)
	{
		if (EvilEraser::IsOKAndTryUse(EvilEraser::BlockTypes::FoxGuard, __instance))
		{
			if (RoleClass::Fox::KillGuard.find(target->PlayerId) == RoleClass::Fox::KillGuard.end())
			{
				target->RpcProtectPlayer(target, 0);
			}
			else
			{
				if (!(RoleClass::Fox::KillGuard[target->PlayerId] <= 0))
				{
					RoleClass::Fox::KillGuard[target->PlayerId]--;
					target->RpcProtectPlayer(target, 0);
				}
			}
		}
	}
}
