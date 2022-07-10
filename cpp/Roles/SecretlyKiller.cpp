#include "SecretlyKiller.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../ModHelpers.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{

	void SecretlyKiller::EndMeeting()
	{
		AllResetCoolDown();
	}

	void SecretlyKiller::MainResetCoolDown()
	{
		//ノーマルリセット
		HudManagerStartPatch::SecretlyKillerMainButton->MaxTimer = RoleClass::SecretlyKiller::KillCoolTime;
		HudManagerStartPatch::SecretlyKillerMainButton->Timer = RoleClass::SecretlyKiller::KillCoolTime;
		//シークレットリーリセット
		/*if (SuperNewRoles.CustomOption.CustomOptions.SecretlyKillerKillCoolTimeChange.getBool()){
		    HudManagerStartPatch.SecretlyKillerSecretlyKillButton.MaxTimer = RoleClass.SecretlyKiller.SecretlyKillerKillCoolTime;
		    HudManagerStartPatch.SecretlyKillerSecretlyKillButton.Timer = RoleClass.SecretlyKiller.SecretlyKillerKillCoolTime;
		}*/
		//RoleClass.SecretlyKiller.ButtonTimer = DateTime.Now;
	}

	void SecretlyKiller::SecretlyResetCoolDown()
	{
		//シークレットリーリセット
		HudManagerStartPatch::SecretlyKillerSecretlyKillButton->MaxTimer = RoleClass::SecretlyKiller::SecretlyKillCoolTime;
		HudManagerStartPatch::SecretlyKillerSecretlyKillButton->Timer = RoleClass::SecretlyKiller::SecretlyKillCoolTime;
		/*//ノーマルリセット
		if (SuperNewRoles.CustomOption.CustomOptions.SecretlyKillerKillCoolTimeChange.getBool()){
		    HudManagerStartPatch.SecretlyKillerMainButton.MaxTimer = RoleClass.SecretlyKiller.SecretlyKillCoolTime;
		    HudManagerStartPatch.SecretlyKillerMainButton.Timer = RoleClass.SecretlyKiller.SecretlyKillCoolTime;
		}*/
		//RoleClass.SecretlyKiller.ButtonTimer = DateTime.Now;
	}

	void SecretlyKiller::AllResetCoolDown()
	{
		//シークレットリーリセット
		HudManagerStartPatch::SecretlyKillerSecretlyKillButton->MaxTimer = RoleClass::SecretlyKiller::SecretlyKillCoolTime;
		HudManagerStartPatch::SecretlyKillerSecretlyKillButton->Timer = RoleClass::SecretlyKiller::SecretlyKillCoolTime;
		//ノーマルリセット
		HudManagerStartPatch::SecretlyKillerMainButton->MaxTimer = RoleClass::SecretlyKiller::KillCoolTime;
		HudManagerStartPatch::SecretlyKillerMainButton->Timer = RoleClass::SecretlyKiller::KillCoolTime;
		//RoleClass.SecretlyKiller.ButtonTimer = DateTime.Now;
	}

	void SecretlyKiller::SecretlyKill()
	{
		RoleClass::SecretlyKiller::target->RpcMurderPlayer(RoleClass::SecretlyKiller::target);
		RoleClass::SecretlyKiller::target = nullptr;
		//MessageWriter killWriter = AmongUsClient.Instance.StartRpcImmediately(CachedPlayer.LocalPlayer.NetId, (byte)CustomRPC.CustomRPC.SheriffKill, Hazel.SendOption.Reliable, -1);
		//killWriter.Write();
		//AmongUsClient.Instance.FinishRpcImmediately(killWriter);
	}

	void SecretlyKiller::setPlayerOutline(PlayerControl *target, Color *color)
	{
		if (target == nullptr || target->MyRend == nullptr)
		{
			return;
		}

		SuperNewRoles::ModHelpers::MyRend(target)->material.SetFloat(L"_Outline", 1.0f);
		SuperNewRoles::ModHelpers::MyRend(target)->material.SetColor(L"_OutlineColor", color);
	}
}
