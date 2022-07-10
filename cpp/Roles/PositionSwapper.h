#pragma once

#include <vector>
#include "../stringhelper.h"

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class PositionSwapper
	{
	public:
		static void ResetCoolDown();
		static void EndMeeting();
		static void SwapStart();
		/*public static Vector3 GetSwapPosition(byte SwapPlayerID, byte SwapperID){
		    var SwapPlayer = ModHelpers.playerById(SwapPlayerID);
		    var SwapperPlayer = ModHelpers.playerById(SwapperID);
		    if (PlayerControl.LocalPlayer.isRole(CustomRPC.RoleId.PositionSwapper)){
		        return SwapPlayer.transform.position;
		    }
		    else{
		        return SwapperPlayer.transform.position;
		    }
		}*/
	};
}
