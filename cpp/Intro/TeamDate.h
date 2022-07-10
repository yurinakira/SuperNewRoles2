#pragma once

#include "../CustomRPC/CustomRPC.h"
#include <string>
#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;
namespace SuperNewRoles::Intro
{
	class TeamDate
	{
	public:
		std::wstring NameKey;
		Color *color;
		Color *BackGround;
		std::vector<CustomRPC::RoleId> RoleIds;

		virtual ~TeamDate()
		{
			delete color;
			delete BackGround;
		}

	private:
		TeamDate(const std::wstring &NameKey, Color *color, Color *BackGround, std::vector<CustomRPC::RoleId> &RoleId);
	public:
		static TeamDate *VultureTeam;
	};
}
