#include "Patch.h"
#include "main.h"
#include "Agartha/Patch/MiniMapPatch.h"

using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles::Map
{

	void Patch::ChangeMapPatch::Postfix(MapBehaviour *__instance)
	{
		if (Data::IsMap(CustomMapNames::Agartha))
		{
			Agartha::Patch::MiniMapPatch::MinimapChange(__instance);
		}
	}
}
