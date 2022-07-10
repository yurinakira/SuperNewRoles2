#pragma once

#include "FixedUpdate.h"

using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
	class Clairvoyant
	{
	public:
		static void TimerEnd();
	private:
		static float count;


		//千里眼機能の中身
	public:
		class FixedUpdate
		{
		public:
			static void Postfix();
		};
	};
}
