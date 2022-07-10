#pragma once

using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class MadHawk
	{
	public:
		static void TimerEnd();
	public:
		class FixedUpdate
		{
		public:
			static void Postfix();
		};
	};
}
