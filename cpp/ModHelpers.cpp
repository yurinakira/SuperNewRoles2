//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "ModHelpers.h"
#include "Helpers/FastDestroyableSingleton.h"
#include "CustomOption/CustomOptionDate.h"
#include "CustomRPC/CustomRPC.h"
#include "Roles/RoleClass.h"
#include "Roles/RoleHelper.h"
#include "Roles/EvilEraser.h"
#include "Helpers/RPCHelper.h"
#include "Helpers/MapUtilities.h"
#include "LateTask.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Roles;
using namespace TMPro;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles
{

	bool ModHelpers::getShowButtons()
	{
		return !(MapBehaviour::Instance && MapBehaviour::Instance->IsOpen) && !MeetingHud::Instance && !ExileController::Instance;
	}

	void ModHelpers::SetKillTimerUnchecked(PlayerControl *player, float time, float max)
	{
		if (max == -std::numeric_limits<float>::infinity())
		{
			max = time;
		}

		player->killTimer = time;
		FastDestroyableSingleton<HudManager*>::getInstance().KillButton::SetCoolDown(time, max);
	}

	Sprite *ModHelpers::CreateSprite(const std::wstring &path, bool fromDisk)
	{
		Texture2D *texture = fromDisk ? ModHelpers::loadTextureFromDisk(path) : ModHelpers::loadTextureFromResources(path);
		if (texture == nullptr)
		{
			return nullptr;
		}
		Rect tempVar(0, 0, texture->width, texture->height);
		Vector2 tempVar2(0.53f, 0.575f);
		Sprite *sprite = Sprite::Create(texture, &tempVar, &tempVar2, texture->width * 0.375f);
		if (sprite == nullptr)
		{
			return nullptr;
		}
		texture->hideFlags |= HideFlags::HideAndDontSave | HideFlags::DontUnloadUnusedAsset;
		sprite->hideFlags |= HideFlags::HideAndDontSave | HideFlags::DontUnloadUnusedAsset;
		return sprite;
	}

	std::optional<unsigned char> ModHelpers::GetKey(std::unordered_map<unsigned char, unsigned char> &dec, unsigned char Value)
	{
		for (auto data : dec)
		{
			if (data.Value == Value)
			{
				return data.Key;
			}
		}
		return std::nullopt;
	}

	std::vector<GameObject*> ModHelpers::GetChildren(GameObject *ParentObject)
	{
		std::vector<GameObject*> ChildObject(ParentObject->transform.childCount);

		for (int i = 0; i < ParentObject->transform.childCount; i++)
		{
			ChildObject[i] = ParentObject->transform.GetChild(i)->gameObject;
		}
		return ChildObject;
	}

	void ModHelpers::DeleteObject(std::vector<Transform*> &trans, const std::wstring &notdelete)
	{
		for (auto tran : trans)
		{
			if (tran->name != notdelete)
			{
				GameObject::Destroy(tran);
			}
		}
	}

	void ModHelpers::DeleteObject(std::vector<GameObject*> &trans, const std::wstring &notdelete)
	{
		for (auto tran : trans)
		{
			if (tran->name != notdelete)
			{
				GameObject::Destroy(tran);
			}
		}
	}

	std::vector<PlayerControl*> ModHelpers::getAllNotDisconnectedPlayerControl()
	{
		std::vector<PlayerControl*> ps;
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (!p->Data->Disconnected)
			{
				ps.push_back(p->PlayerControl);
			}
		}
		return ps;
	}

	void ModHelpers::SetActiveAllObject(std::vector<GameObject*> &trans, const std::wstring &notdelete, bool IsActive)
	{
		for (auto tran : trans)
		{
			if (tran->name != notdelete)
			{
				tran->SetActive(IsActive);
			}
		}
	}

	void ModHelpers::setSkinWithAnim(PlayerPhysics *playerPhysics, const std::wstring &SkinId)
	{
		SkinViewData *nextSkin = DestroyableSingleton<HatManager*>::Instance->GetSkinById(SkinId).viewData.viewData;
		AnimationClip *clip = nullptr;
		auto spriteAnim = SuperNewRoles::ModHelpers::GetSkin(playerPhysics)->animator;
		auto anim = spriteAnim->m_animator;
		auto skinLayer = SuperNewRoles::ModHelpers::GetSkin(playerPhysics);

		auto currentPhysicsAnim = playerPhysics->Animator.GetCurrentAnimation();
		if (currentPhysicsAnim == playerPhysics->CurrentAnimationGroup.RunAnim)
		{
			clip = nextSkin->RunAnim;
		}
		else if (currentPhysicsAnim == playerPhysics->CurrentAnimationGroup.SpawnAnim)
		{
			clip = nextSkin->SpawnAnim;
		}
		else if (currentPhysicsAnim == playerPhysics->CurrentAnimationGroup.EnterVentAnim)
		{
			clip = nextSkin->EnterVentAnim;
		}
		else if (currentPhysicsAnim == playerPhysics->CurrentAnimationGroup.ExitVentAnim)
		{
			clip = nextSkin->ExitVentAnim;
		}
		else if (currentPhysicsAnim == playerPhysics->CurrentAnimationGroup.IdleAnim)
		{
			clip = nextSkin->IdleAnim;
		}
		else
		{
			clip = nextSkin->IdleAnim;
		}

		float progress = playerPhysics->Animator.m_animator.GetCurrentAnimatorStateInfo(0).normalizedTime;
		skinLayer->skin = nextSkin;

		spriteAnim->Play(clip, 1.0f);
		anim->Play(L"a", 0, progress % 1);
		anim->Update(0.0f);
	}

	std::unordered_map<unsigned char, PlayerControl*> ModHelpers::allPlayersById()
	{
		std::unordered_map<unsigned char, PlayerControl*> res;
		for (auto player : CachedPlayer::AllPlayers)
		{
			res.emplace(player->PlayerId, player);
		}
		return res;
	}

	ModHelpers::MurderAttemptResult ModHelpers::checkMuderAttempt(PlayerControl *killer, PlayerControl *target, bool blockRewind)
	{
		// Modified vanilla checks
		if (AmongUsClient::Instance->IsGameOver)
		{
			return MurderAttemptResult::SuppressKill;
		}
		if (killer == nullptr || killer->Data == nullptr || killer->Data->IsDead || killer->Data->Disconnected)
		{
			return MurderAttemptResult::SuppressKill; // Allow non Impostor kills compared to vanilla code
		}
		if (target == nullptr || target->Data == nullptr || target->Data->IsDead || target->Data->Disconnected)
		{
			return MurderAttemptResult::SuppressKill; // Allow killing players in vents compared to vanilla code
		}
		if (SuperNewRoles::RoleHelpers::isRole(target, RoleId::StuntMan) && !SuperNewRoles::RoleHelpers::isRole(killer, RoleId::OverKiller) && (RoleClass::StuntMan::GuardCount.find(target->PlayerId) == RoleClass::StuntMan::GuardCount.end() || RoleClass::StuntMan::GuardCount[target->PlayerId] >= 1))
		{
			if (EvilEraser::IsOKAndTryUse(EvilEraser::BlockTypes::StuntmanGuard, killer))
			{
				bool IsSend = false;
				if (RoleClass::StuntMan::GuardCount.find(target->PlayerId) == RoleClass::StuntMan::GuardCount.end())
				{
					MessageWriter *writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::UncheckedProtect);
					writer->Write(target->PlayerId);
					writer->Write(target->PlayerId);

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
