#include "Doorr.h"
#include "../Helpers/CachedPlayer.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../ModHelpers.h"
#include "../Helpers/MapUtilities.h"

using namespace SuperNewRoles::Buttons;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Doorr::ResetCoolDown()
	{
		if (CachedPlayer::LocalPlayer->Data->Role.IsImpostor)
		{
			HudManagerStartPatch::DoorrDoorButton->MaxTimer = RoleClass::EvilDoorr::CoolTime;
		}
		else
		{
			HudManagerStartPatch::DoorrDoorButton->MaxTimer = RoleClass::Doorr::CoolTime;
		}
		RoleClass::Doorr::ButtonTimer = DateTime::Now;
	}

	bool Doorr::isDoorr(PlayerControl *Player)
	{
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Doorr::DoorrPlayer, Player) || SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::EvilDoorr::EvilDoorrPlayer, Player))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Doorr::CheckTarget()
	{
		PlainDoor *door = GetDoor();
		if (door == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void Doorr::DoorrBtn()
	{
		PlainDoor *door = GetDoor();
		if (door != nullptr)
		{
			door->SetDoorway(!door->Open);
		}
	}

	float Doorr::IsPos(Vector3 *mypos, PlainDoor *Door, float distance)
	{
		auto Distance = Vector3::Distance(mypos, Door->transform.position);
		if (Distance <= distance)
		{
			return Distance;
		}
		return 0.0f;
	}

	PlainDoor *Doorr::GetDoor()
	{
		Vector3 *position = CachedPlayer::LocalPlayer->transform->position;
		std::vector<PlainDoor*> selectdoors;
		for (PlainDoor *door : MapUtilities::CachedShipStatus->AllDoors)
		{
			auto getispos = IsPos(position, door, 2);
			if (getispos != 0)
			{
				selectdoors.push_back(door);
			}
		}
		bool flag = true;
		while (flag)
		{
			if (selectdoors.size() >= 2)
			{
				if (IsPos(position, selectdoors[0], 2) >= IsPos(position, selectdoors[1], 2))
				{
					selectdoors.Remove(selectdoors[0]);
				}
				else
				{
					selectdoors.Remove(selectdoors[1]);
				}
			}
			else
			{
				flag = false;
			}
		}
		return selectdoors[0];
	}

	void Doorr::EndMeeting()
	{
		if (CachedPlayer::LocalPlayer->Data->Role.IsImpostor)
		{
			HudManagerStartPatch::DoorrDoorButton->MaxTimer = RoleClass::EvilDoorr::CoolTime;
		}
		else
		{
			HudManagerStartPatch::DoorrDoorButton->MaxTimer = RoleClass::Doorr::CoolTime;
		}
		RoleClass::Doorr::ButtonTimer = DateTime::Now;
	}
}
