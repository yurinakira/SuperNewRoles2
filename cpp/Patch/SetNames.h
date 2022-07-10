#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <limits>
#include <optional>
#include "../stringhelper.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Roles;
using namespace TMPro;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
	class SetNamesClass
	{
	public:
		static std::unordered_map<int, std::wstring> AllNames;

		static void SetPlayerNameColor(PlayerControl *p, Color *color);
		static void SetPlayerNameText(PlayerControl *p, const std::wstring &text);
		static void resetNameTagsAndColors();
		static std::unordered_map<unsigned char, TextMeshPro*> PlayerInfos;
		static std::unordered_map<unsigned char, TextMeshPro*> MeetingPlayerInfos;

		static void SetPlayerRoleInfoView(PlayerControl *p, Color *roleColors, const std::wstring &roleNames, std::optional<Color*> &GhostRoleColor = std::nullopt, const std::wstring &GhostRoleNames = L"");
		static void SetPlayerRoleInfo(PlayerControl *p);
		static void SetPlayerNameColors(PlayerControl *player);
		static void SetPlayerRoleNames(PlayerControl *player);
		static void QuarreledSet();
		static void LoversSet();
		static void DemonSet();
		static void ArsonistSet();
		static void CelebritySet();
	};
	class SetNameUpdate
	{
	public:
		static void Postfix(PlayerControl *__instance);
	};
}
