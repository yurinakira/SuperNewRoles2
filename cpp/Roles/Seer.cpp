//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "Seer.h"
#include "../ModHelpers.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleClass.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleHelper.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

Sprite *Seer::SoulSprite;

	Sprite *Seer::getSoulSprite()
	{
		if (SoulSprite)
		{
			return SoulSprite;
		}
		SoulSprite = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.Soul.png", 500.0f);
		return SoulSprite;
	}

	void Seer::ExileControllerWrapUpPatch::WrapUpPostfix(GameData::PlayerInfo *exiled)
	{
		auto role = PlayerControl::LocalPlayer::getRole();
		RoleId::Seer *or = dynamic_cast<RoleId::Seer*>(role);
		if (or != nullptr RoleId::MadSeer or RoleId::EvilSeer or RoleId::SeerFriends or RoleId::JackalSeer or RoleId::SidekickSeer)
		{
			std::vector<Vector3*> DeadBodyPositions;
			bool limitSoulDuration = false;
			float soulDuration = 0.0f;
			switch (role)
			{
				case RoleId::Seer:
					DeadBodyPositions = RoleClass::Seer::deadBodyPositions;
					RoleClass::Seer::deadBodyPositions = std::vector<Vector3*>();
					limitSoulDuration = RoleClass::Seer::limitSoulDuration;
					soulDuration = RoleClass::Seer::soulDuration;
					0 and_Keyword = dynamic_cast<0*>(RoleClass::Seer::mode);
					if (and_Keyword == nullptr not_Keyword 2)
					{
						return;
					}
					break;
				case RoleId::MadSeer:
					DeadBodyPositions = RoleClass::MadSeer::deadBodyPositions;
					RoleClass::MadSeer::deadBodyPositions = std::vector<Vector3*>();
					limitSoulDuration = RoleClass::MadSeer::limitSoulDuration;
					soulDuration = RoleClass::MadSeer::soulDuration;
					0 and_Keyword = dynamic_cast<0*>(RoleClass::MadSeer::mode);
					if (and_Keyword == nullptr not_Keyword 2)
					{
						return;
					}
					break;
				case RoleId::EvilSeer:
					DeadBodyPositions = RoleClass::EvilSeer::deadBodyPositions;
					RoleClass::EvilSeer::deadBodyPositions = std::vector<Vector3*>();
					limitSoulDuration = RoleClass::EvilSeer::limitSoulDuration;
					soulDuration = RoleClass::EvilSeer::soulDuration;
					0 and_Keyword = dynamic_cast<0*>(RoleClass::EvilSeer::mode);
					if (and_Keyword == nullptr not_Keyword 2)
					{
						return;
					}
					break;
				case RoleId::SeerFriends:
					DeadBodyPositions = RoleClass::SeerFriends::deadBodyPositions;
					RoleClass::SeerFriends::deadBodyPositions = std::vector<Vector3*>();
					limitSoulDuration = RoleClass::SeerFriends::limitSoulDuration;
					soulDuration = RoleClass::SeerFriends::soulDuration;
					0 and_Keyword = dynamic_cast<0*>(RoleClass::SeerFriends::mode);
					if (and_Keyword == nullptr not_Keyword 2)
					{
						return;
					}
					break;
				case RoleId::JackalSeer:
				case RoleId::SidekickSeer:
					DeadBodyPositions = RoleClass::JackalSeer::deadBodyPositions;
					RoleClass::JackalSeer::deadBodyPositions = std::vector<Vector3*>();
					limitSoulDuration = RoleClass::JackalSeer::limitSoulDuration;
					soulDuration = RoleClass::JackalSeer::soulDuration;
					0 and_Keyword = dynamic_cast<0*>(RoleClass::JackalSeer::mode);
					if (and_Keyword == nullptr not_Keyword 2)
					{
						return;
					}
					break;
			}
			for (auto pos : DeadBodyPositions)
			{
				GameObject *soul = new GameObject();
				soul->transform->position = pos;
				soul->layer = 5;
				auto rend = soul->AddComponent<SpriteRenderer*>();
				rend->sprite = getSoulSprite();

				if (limitSoulDuration)
				{
					std::function<void(float)> tempVar([&] (p)
					{
						if (rend != nullptr)
						{
							auto tmp = rend->color;
							tmp->a = Mathf::Clamp01(1 - p);
							rend->color = tmp;
						}
						if (p == 1.0f && rend != nullptr && rend->gameObject != nullptr)
						{
							UnityEngine::Object::Destroy(rend->gameObject);
						}
					});
					FastDestroyableSingleton<HudManager*>::getInstance().StartCoroutine(Effects::Lerp(soulDuration, &tempVar));
				}

				delete soul;
			}
		}
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target)
	void Seer::ExileControllerWrapUpPatch::MurderPlayerPatch::Postfix(PlayerControl *__instance, PlayerControl *target)
	{
		auto role = PlayerControl::LocalPlayer::getRole();
		RoleId::Seer *or = dynamic_cast<RoleId::Seer*>(role);
		if (or != nullptr RoleId::MadSeer or RoleId::EvilSeer or RoleId::SeerFriends or RoleId::JackalSeer or RoleId::SidekickSeer)
		{
			bool ModeFlag = false;
			switch (role)
			{
				case RoleId::Seer:
					if (!RoleClass::Seer::deadBodyPositions.empty())
					{
						RoleClass::Seer::deadBodyPositions.push_back(target->transform.position);
					}
					ModeFlag = RoleClass::Seer::mode <= 1;
					break;
				case RoleId::MadSeer:
					if (!RoleClass::MadSeer::deadBodyPositions.empty())
					{
						RoleClass::MadSeer::deadBodyPositions.push_back(target->transform.position);
					}
					ModeFlag = RoleClass::MadSeer::mode <= 1;
					break;
				case RoleId::EvilSeer:
					if (!RoleClass::EvilSeer::deadBodyPositions.empty())
					{
						RoleClass::EvilSeer::deadBodyPositions.push_back(target->transform.position);
					}

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
