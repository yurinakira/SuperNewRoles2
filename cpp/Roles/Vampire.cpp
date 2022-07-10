#include "Vampire.h"
#include "RoleClass.h"
#include "../Main.h"

namespace SuperNewRoles::Roles
{

	void Vampire::FixedUpdate::Postfix()
	{
		if (RoleClass::Vampire::target == nullptr)
		{
			return;
		}
		auto TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(RoleClass::Vampire::KillDelay));
		RoleClass::Vampire::Timer = static_cast<float>(((Roles->RoleClass.Vampire::KillTimer + TimeSpanDate) - DateTime::Now).TotalSeconds);
		SuperNewRolesPlugin::Logger->LogInfo(L"ヴァンパイア:" + std::to_wstring(RoleClass::Vampire::Timer));
		if (RoleClass::Vampire::Timer <= 0.1)
		{
			RoleClass::Vampire::target->RpcMurderPlayer(RoleClass::Vampire::target);
			RoleClass::Vampire::target = nullptr;
		}
	}
}
