#include "NotBlackOut.h"
#include "../ModeHandler.h"
#include "../SuperHostRoles/MorePatch.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::NotImpostorCheck
{

	void NotBlackOut::CheckForEndVotingPatch::Prefix(MeetingHud *__instance)
	{
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {Mode::ModeId::NotImpostorCheck}))
		{
			EndMeetingPatch();
		}
		else if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			SuperHostRoles::MorePatch::MeetingEnd();
		}
	}

	void NotBlackOut::EndMeetingPatch()

	{
	/*
	    //霊界用暗転バグ対処
	    foreach (var pc in CachedPlayer.AllPlayers)
	        if (main.Impostors.Contains(pc.PlayerId) && pc.Data.IsDead) pc.ResetPlayerCam(12.5f);
	}
	public static void ResetPlayerCam(this PlayerControl pc, float delay = 0f)
	{
		if ((UnityEngine.Object)(object)pc == (UnityEngine.Object)null || !AmongUsClient.Instance.AmHost || pc.AmOwner)
		{
			return;
		}
		int clientId = pc.getClientId();
		byte reactorId = 3;
		if (PlayerControl.GameOptions.MapId == 2)
		{
			reactorId = 21;
		}
		AmongUsClient.Instance.StartCoroutine(nameof(ReactorDesync));
		AmongUsClient.Instance.StartCoroutine(nameof(MurderToResetCam));
		AmongUsClient.Instance.StartCoroutine(nameof(FixDesyncReactor));
		IEnumerator ReactorDesync()
		{
			yield return new WaitForSeconds(delay);
			MessageWriter val4 = AmongUsClient.Instance.StartRpcImmediately(MapUtilities.CachedShipStatus.NetId, 28, (SendOption)1, clientId);
			val4.Write(reactorId);
			val4.WriteNetObject(pc);
			val4.Write((byte)128);
			AmongUsClient.Instance.FinishRpcImmediately(val4);
		}
		IEnumerator MurderToResetCam()
		{
			yield return new WaitForSeconds(0.2f+delay);
			MessageWriter val3 = AmongUsClient.Instance.StartRpcImmediately(pc.NetId, 12, (SendOption)1, clientId);
			val3.WriteNetObject(pc);
			AmongUsClient.Instance.FinishRpcImmediately(val3);
		}
		IEnumerator FixDesyncReactor()
		{
			yield return new WaitForSeconds(0.4f + delay);
			MessageWriter val2 = AmongUsClient.Instance.StartRpcImmediately(MapUtilities.CachedShipStatus.NetId, 28, (SendOption)1, clientId);
			val2.Write(reactorId);
			val2.WriteNetObject(pc);
			val2.Write((byte)16);
			AmongUsClient.Instance.FinishRpcImmediately(val2);
		};
		if (PlayerControl.GameOptions.MapId == 4)
		{
			AmongUsClient.Instance.StartCoroutine(nameof(FixDesyncReactor2));
			IEnumerator FixDesyncReactor2()
			{
				yield return new WaitForSeconds(0.4f + delay);
				MessageWriter val = AmongUsClient.Instance.StartRpcImmediately(MapUtilities.CachedShipStatus.NetId, 28, (SendOption)1, clientId);
				val.Write(reactorId);
				val.WriteNetObject(pc);
				val.Write((byte)17);
				AmongUsClient.Instance.FinishRpcImmediately(val);
			}
		}
	*/
	}
}
