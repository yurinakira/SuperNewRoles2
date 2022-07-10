#include "FixedUpdate.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../Main.h"
#include "../../Roles/RoleClass.h"
#include "../../ModHelpers.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::RandomColor
{

int FixedUpdate::MaxColorCount = 15;
float FixedUpdate::UpdateTime = 0;
bool FixedUpdate::IsRandomNameColor = false;
bool FixedUpdate::IsHideName = false;
bool FixedUpdate::IsHideNameSet = false;
bool FixedUpdate::IsRandomColorMeeting = false;
bool FixedUpdate::IsMeetingIn = false;

	void FixedUpdate::Update()
	{
		if (!IsHideNameSet)
		{
			IsHideNameSet = true;
			if (IsHideName)
			{
				for (auto p : CachedPlayer::AllPlayers)
				{
					if (!p->Data->Disconnected)
					{
						p->RpcSetName(L"  ");
					}
				}
			}
		}
		UpdateTime -= Time::fixedDeltaTime;
		if (UpdateTime <= 0)
		{
			UpdateTime = 0.1f;
			for (auto p : CachedPlayer::AllPlayers)
			{
				if (!p->Data->Disconnected)
				{
					unsigned char SetColor = static_cast<unsigned char>(p->Data->DefaultOutfit.ColorId + 1);
					if (p->Data->DefaultOutfit.ColorId >= MaxColorCount - 1)
					{
						SetColor = 0;
					}
					SuperNewRolesPlugin::Logger->LogInfo(L"[RandomColor] UPDATED!");
					if (!RoleClass::IsMeeting || (RoleClass::IsMeeting && IsRandomColorMeeting))
					{
						p->RpcSetColor(SetColor);
					}
					if (!IsHideName && IsRandomNameColor && (!RoleClass::IsMeeting || (RoleClass::IsMeeting && IsRandomColorMeeting)))
					{
						p->RpcSetName(ModHelpers::cs(Palette->PlayerColors[SetColor], SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(p)));
					}
					if (RoleClass::IsMeeting && IsHideName)
					{
						p->RpcSetName(ModHelpers::cs(Color::yellow, L"[RandomColor] RandomColorMode!"));
						IsMeetingIn = true;
					}
					if (IsMeetingIn && !RoleClass::IsMeeting && IsHideName)
					{
						IsHideNameSet = false;
					}
				}
			}
		}
	}
}
