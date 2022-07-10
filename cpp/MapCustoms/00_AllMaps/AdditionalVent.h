#pragma once

#include <vector>
#include <iostream>

using namespace HarmonyLib;
using namespace SuperNewRoles::MapOptions;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

//参考=>https://github.com/haoming37/TheOtherRoles-GM-Haoming/blob/haoming-main/TheOtherRoles/Objects/AdditionalVents.cs

namespace SuperNewRoles::MapCustoms
{
	class AdditionalVents
	{
	public:
		Vent *vent;
		static std::vector<AdditionalVents*> AllVents;
		static bool flag;
		virtual ~AdditionalVents()
		{
			delete vent;
		}

		AdditionalVents(Vector3 *p);

		static void AddAdditionalVents();

		static void ClearAndReload();
	};
}
