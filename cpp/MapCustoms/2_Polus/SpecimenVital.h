#pragma once

using namespace UnityEngine;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::MapCustoms
{
	class SpecimenVital
	{
	public:
		static Vector3 *pos;
		static bool flag;
		static void ClearAndReload();

		static void moveVital();
	};
}
