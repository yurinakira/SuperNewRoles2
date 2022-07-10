//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "SecretRoom.h"
#include "../../ModHelpers.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../LateTask.h"
#include "../../Roles/RoleHelper.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../../Helpers/RPCHelper.h"
#include "../../Roles/RoleClass.h"

using namespace BepInEx::IL2CPP::Utils;
using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Roles;
using namespace TMPro;
using namespace UnityEngine;

namespace SuperNewRoles::MapCustoms::Airship
{

PlayerControl *SecretRoom::leftplayer;
PlayerControl *SecretRoom::rightplayer;
PoolablePlayer *SecretRoom::left;
PoolablePlayer *SecretRoom::right;
PlayerControl *SecretRoom::UsePlayer;
bool SecretRoom::IsWait = false;
TextMeshPro *SecretRoom::LowerInfoText;
std::vector<Vector2*> SecretRoom::TeleportPositions =
{
	new Vector2(-0.78f, -1.0f),
	new Vector2(-13, -1),
	new Vector2(-13, 1.5f),
	new Vector2(-21, -1.2f),
	new Vector2(-10, -7),
	new Vector2(-6.2f, -11),
	new Vector2(-13.4f, -12.2f),
	new Vector2(2.2f, -12),
	new Vector2(7.2f, -11.4f),
	new Vector2(16.3f, -8.6f),
	new Vector2(24.9f, -5.7f),
	new Vector2(33.6f, -0.6f),
	new Vector2(31.5f, 5.6f),
	new Vector2(20.0f, 10.1f),
	new Vector2(12.6f, 9.1f),
	new Vector2(19.5f, 0.1f),
	new Vector2(11.1f, 0),
	new Vector2(-0.7f, 8.6f),
	new Vector2(-9.0f, 12.7f),
	new Vector2(4.1f, 8.7f),
	new Vector2(11, 16)
};

	void SecretRoom::SetSecretRoomTeleportStatus(Status status, unsigned char data1, unsigned char data2)
	{
		switch (status)
		{
			case Status::UseConsole:
			{
				PlayerControl *useplayer = ModHelpers::playerById(data1);
				if (UsePlayer != nullptr)
				{
					if (data1 == CachedPlayer::LocalPlayer->PlayerId)
					{
						VitalsMinigame *minigame = GameObject::FindObjectOfType<VitalsMinigame*>();
						if (minigame != nullptr && minigame->name == L"secretroom_teleport-console")
						{
							minigame->Close();
						}
					}
					return;
				}
				if (useplayer == nullptr)
				{
					return;
				}
				UsePlayer = useplayer;
				break;
			}
			case Status::CloseConsole:
				UsePlayer = nullptr;
				IsWait = false;
				if ((leftplayer != nullptr && leftplayer->PlayerId == CachedPlayer::LocalPlayer->PlayerId) || (rightplayer != nullptr && rightplayer->PlayerId == CachedPlayer::LocalPlayer->PlayerId))
				{
					LowerInfoText->text = L"Escで実験から抜ける";
				}
				break;
			case Status::Join:
			{
				PlayerControl *player = ModHelpers::playerById(data1);
				if (player == nullptr)
				{
					return;
				}
				if (data2 == 0)
				{
					leftplayer = player;
				}
				else
				{
					rightplayer = player;
				}
				break;
			}
			case Status::Break:
				if (data1 == 0)
				{
					leftplayer = nullptr;
				}
				else
				{
					rightplayer = nullptr;
				}
				break;
			case Status::Wait:
				if ((leftplayer != nullptr && leftplayer->PlayerId == CachedPlayer::LocalPlayer->PlayerId) || (rightplayer != nullptr && rightplayer->PlayerId == CachedPlayer::LocalPlayer->PlayerId))
				{
					PlayerControl::LocalPlayer->moveable = false;
					LowerInfoText->text = L"実験中...";
				}
				IsWait = true;
				break;
			case Status::Teleport:
				if ((leftplayer != nullptr && leftplayer->PlayerId == CachedPlayer::LocalPlayer->PlayerId) || (rightplayer != nullptr && rightplayer->PlayerId == CachedPlayer::LocalPlayer->PlayerId))
				{
					PlayerControl::LocalPlayer->moveable = true;
					PlayerControl::LocalPlayer::transform->position = ModHelpers::GetRandom<Vector2*>(TeleportPositions);
				}
				IsWait = false;
				rightplayer = nullptr;
				leftplayer = nullptr;
				UsePlayer = nullptr;
				break;
		}
	}

	void SecretRoom::Reset()
	{
		IsWait = false;
		leftplayer = nullptr;
		rightplayer = nullptr;
		UsePlayer = nullptr;
	}

	void SecretRoom::ShipStatusAwake(ShipStatus *__instance)
	{
		if (PlayerControl::GameOptions::MapId != static_cast<int>(MapNames::Airship))
		{
			return;
		}
		if (__instance->Type == ShipStatus::MapType::Ship && MapCustom::SecretRoomOption->getBool())
		{

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
