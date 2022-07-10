#include "TeamDate.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Intro
{

	TeamDate::TeamDate(const std::wstring &NameKey, Color *color, Color *BackGround, std::vector<CustomRPC::RoleId> &RoleId)
	{
		this->color = color;
		this->BackGround = BackGround;
		this->NameKey = NameKey;
		this->RoleIds = RoleId;
	}

TeamDate *TeamDate::VultureTeam = new TeamDate(L"Test", Color::black, Color::yellow, std::vector<CustomRPC::RoleId> {CustomRPC::RoleId::Sheriff});
}
