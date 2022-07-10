#pragma once

using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Hawk
	{
	public:
		static void TimerEnd();
	private:
		static float count;
	public:
		class FixedUpdate
		{
		public:
			static void Postfix();
		};
	};
}
