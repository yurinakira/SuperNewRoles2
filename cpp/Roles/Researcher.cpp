#include "Researcher.h"
#include "../Helpers/FastDestroyableSingleton.h"

using namespace HarmonyLib;

namespace SuperNewRoles::Roles
{

	bool Researcher::IsTarget()
	{
		/**
		Vector3 position = CachedPlayer.LocalPlayer.transform.position;
		Vector3 SamplePos = RoleClass.Researcher.SamplePosition;
		int r = 1;
		if ((position.x + r >= SamplePos.x) && (SamplePos.x >= position.x - r))
		{
		    if ((position.y + r >= SamplePos.y) && (SamplePos.y >= position.y - r))
		    {
		        if ((position.z + r >= SamplePos.z) && (SamplePos.z >= position.z - r))
		        {
		            return true ;
		        }
		    }
		}
		**/
		return false;
	}

	void Researcher::UseButtonUsePatch::Postfix(UseButton *__instance)
	{
		/**
		if (AmongUsClient.Instance.GameState != AmongUsClient.GameStates.Started) return;
		if (!RoleClass.Researcher.ResearcherPlayer.IsCheckListPlayerControl(PlayerControl.LocalPlayer)) return;
	
		Vector3 position = CachedPlayer.LocalPlayer.transform.position;
		Vector3 SamplePos = RoleClass.Researcher.SamplePosition;
		SuperNewRolesPlugin.Logger.LogInfo("pos:"+position);
		SuperNewRolesPlugin.Logger.LogInfo("Samplepos:"+SamplePos);
		if (IsTarget()) {
		    SuperNewRolesPlugin.Logger.LogInfo("TARGETOK");
		    if (RoleClass.Researcher.MySample == 0) {
		        SuperNewRolesPlugin.Logger.LogInfo("SAMPLED!!!");
		        //RoleClass.Researcher.MySample--;
		        SoundManager.Instance.PlaySound(Minigame.Instance.OpenSound, false);
		        //RoleClass.Researcher.OKSamplePlayers.Add(RoleClass.Researcher.GetSamplePlayers[0]);
		        //RoleClass.Researcher.GetSamplePlayers.RemoveAt(0);
		    }
		}
		**/
	}

	void Researcher::ReseUseButtonSetTargetPatch::Postfix(PlayerControl *__instance)
	{
		if (IsTarget())
		{
			FastDestroyableSingleton<HudManager*>::getInstance().UseButton::SetEnabled();
		}
	}
}
