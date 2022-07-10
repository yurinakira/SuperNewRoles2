//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "MeetingSheriff_Patch.h"
#include "RoleClass.h"
#include "../TranslateDate.h"
#include "../ModHelpers.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/CachedPlayer.h"
#include "CountChanger.h"
#include "TeamRoleType.h"
#include "RoleHelper.h"
#include "../Patch/LadderDead.h"
#include "../Mode/ModeHandler.h"
#include "../Mode/SuperHostRoles/MorePatch.h"
#include "../BotManager.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void MeetingUpdatePatch::Postfix(MeetingHud *__instance)
	{
		if (RoleClass::Assassin::TriggerPlayer != nullptr)
		{
			__instance->TitleText->text = ModTranslation::getString(L"MarineWhois");
		}
		if (!IsFlag)
		{
			return;
		}
		if (Input->GetKeyDown(KeyCode::RightArrow))
		{
			MeetingSheriff_Patch::right();
		}
		else if (Input->GetKeyDown(KeyCode::LeftArrow))
		{
			MeetingSheriff_Patch::left();
		}
		meetingsheriff_updatepatch::Change(__instance, false);
	}

PassiveButton *MeetingUpdatePatch::RightButton;
PassiveButton *MeetingUpdatePatch::LeftButton;
bool MeetingUpdatePatch::IsFlag = false;
bool MeetingUpdatePatch::IsSHRFlag = false;
Sprite *MeetingUpdatePatch::m_Meeting_AreaTabChange;

	Sprite *MeetingUpdatePatch::getMeetingAreaTabChange()
	{
		if (m_Meeting_AreaTabChange == nullptr)
		{
			m_Meeting_AreaTabChange = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.Meeting_AreaTabChange.png", 110.0f);
		}
		return m_Meeting_AreaTabChange;
	}

	void meetingsheriff_updatepatch::Postfix(MeetingHud *__instance)
	{
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::MeetingSheriff) && PlayerControl::LocalPlayer::isDead())
		{
			__instance->playerStates.ToList()->ForEach([&] (std::any x)
			{
				if (x::transform::FindChild(L"ShootButton") != nullptr)
				{
					UnityEngine::Object::Destroy(x::transform::FindChild(L"ShootButton").gameObject);
				}
			});
		}
	}

	void meetingsheriff_updatepatch::Change(MeetingHud *__instance, bool right)
	{
		if (!(meetingsheriff_updatepatch::index < (CachedPlayer::AllPlayers.size() / 15) + 1))
		{
			MeetingSheriff_Patch::Right->SetActive(false);
		}
		else
		{
			MeetingSheriff_Patch::Right->SetActive(true);
		}
		if (index <= 1)
		{
			MeetingSheriff_Patch::Left->SetActive(false);
		}
		else
		{
			MeetingSheriff_Patch::Left->SetActive(true);
		}
		int i = 0;
		for (auto area : PlayerVoteAreas)
		{
			try
			{
				if (!(index * 15 < i && i >= 15 * (index - 1)))
				{
					area->transform->localPosition = Positions[i - ((index - 1) * 15)];
				}
				else
				{
					area->transform->localPosition = new Vector3(100, 100, 100);
				}
			}
			catch (...)
			{
				area->transform->localPosition = new Vector3(100, 100, 100);
			}
			i++;
		}
	}

int meetingsheriff_updatepatch::index = 0;
std::vector<PlayerVoteArea*> meetingsheriff_updatepatch::PlayerVoteAreas;
std::vector<Vector3*> meetingsheriff_updatepatch::Positions =
{
	new Vector3(-3.1f, 1.5f, -0.9f),
	new Vector3(-0.2f, 1.5f, -0.9f),
	new Vector3(2.7f, 1.5f, -0.9f),
	new Vector3(-3.1f, 0.74f, -0.91f),
	new Vector3(-0.2f, 0.74f, -0.91f),
	new Vector3(2.7f, 0.74f, -0.91f),
	new Vector3(-3.1f, -0.02f, -0.92f),
	new Vector3(-0.2f, -0.02f, -0.92f),
	new Vector3(2.7f, -0.02f, -0.92f),
	new Vector3(-3.1f, -0.78f, -0.93f),
	new Vector3(-0.2f, -0.78f, -0.93f),
	new Vector3(2.7f, -0.78f, -0.93f),
	new Vector3(-3.1f, -1.54f, -0.94f),
	new Vector3(-0.2f, -1.54f, -0.94f),
	new Vector3(2.7f, -1.54f, -0.94f)
};

	bool MeetingSheriff_Patch::IsMeetingSheriffKill(PlayerControl *Target)
	{
		auto roledata = CountChanger::GetRoleType(Target);
		if (roledata == TeamRoleType::Impostor)
		{
			return true;
		}
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::MadMate::MadMatePlayer, Target) && RoleClass::MeetingSheriff::MadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::MadMate::MadMatePlayer, Target) && RoleClass::MeetingSheriff::MadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::MadJester::MadJesterPlayer, Target) && RoleClass::MeetingSheriff::MadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isNeutral(Target) && RoleClass::MeetingSheriff::NeutralKill)
		{
			return true;
		}
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::MadStuntMan::MadStuntManPlayer, Target) && RoleClass::MeetingSheriff::MadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::MadMayor::MadMayorPlayer, Target) && RoleClass::MeetingSheriff::MadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::MadHawk::MadHawkPlayer, Target) && RoleClass::MeetingSheriff::MadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::MadSeer::MadSeerPlayer, Target) && RoleClass::MeetingSheriff::MadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::JackalFriends::JackalFriendsPlayer, Target) && RoleClass::MeetingSheriff::MadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::SeerFriends::SeerFriendsPlayer, Target) && RoleClass::MeetingSheriff::MadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::HauntedWolf::HauntedWolfPlayer, Target))
		{
			return true;
		}
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::BlackCat::BlackCatPlayer, Target) && RoleClass::MeetingSheriff::MadRoleKill)
		{
			return true;
		}
		return false;
	}

	void MeetingSheriff_Patch::MeetingSheriffOnClick(int Index, MeetingHud *__instance)
	{

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
