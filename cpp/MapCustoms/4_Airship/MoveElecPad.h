#pragma once

using namespace UnityEngine;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::MapCustoms
{
	class MoveElecPad
	{
	public:
		static Vector3 *Meetpos; //ミーティング
		static Vector3 *Safepos; //金庫タスク
		static bool flag;
		static void ClearAndReload();

		static void MoveElecPads();
	};
}
