#include "Patch.h"
#include "4_Airship/SecretRoom.h"

using namespace HarmonyLib;
using namespace static PlayerControl;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::MapCustoms
{

	void Patch::ShipStatus_AwakePatch::Postfix(ShipStatus *__instance)
	{
		Airship::SecretRoom::ShipStatusAwake(__instance);
	}
}
