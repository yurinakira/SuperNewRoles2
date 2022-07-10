#include "Scientist.h"
#include "RoleClass.h"
#include "../Buttons/Buttons.h"
#include "../Helpers/CachedPlayer.h"
#include "../CustomRPC/CustomRPC.h"
#include "SpeedBooster.h"
#include "../ModHelpers.h"
#include "../Mode/ModeHandler.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Scientist::EndMeeting()
	{
		ResetScientist();
		ScientistEnd();
		ResetCoolDown();
	}

	void Scientist::ResetCoolDown()
	{
		float CoolTime;
		if (PlayerControl::LocalPlayer::isImpostor())
		{
			CoolTime = RoleClass::EvilScientist::CoolTime;
		}
		else
		{
			CoolTime = RoleClass::NiceScientist::CoolTime;
		}
		HudManagerStartPatch::ScientistButton->MaxTimer = CoolTime;
		RoleClass::NiceScientist::ButtonTimer = DateTime::Now;
	}

	void Scientist::Start()
	{
		RoleClass::NiceScientist::IsScientist = true;
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetScientistRPC), Hazel::SendOption::Reliable, -1);
		writer->Write(true);
		writer->Write(CachedPlayer::LocalPlayer->PlayerId);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		CustomRPC::RPCProcedure::SetScientistRPC(true, CachedPlayer::LocalPlayer->PlayerId);
		SpeedBooster::ResetCoolDown();
	}

	void Scientist::ResetScientist()
	{
	}

	void Scientist::ScientistEnd()
	{
		RoleClass::NiceScientist::IsScientist = false;
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetScientistRPC), Hazel::SendOption::Reliable, -1);
		writer->Write(false);
		writer->Write(CachedPlayer::LocalPlayer->PlayerId);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		CustomRPC::RPCProcedure::SetScientistRPC(false, CachedPlayer::LocalPlayer->PlayerId);
		ResetScientist();
	}

	void Scientist::setOpacity(PlayerControl *player, float opacity, bool cansee)
	{
		// Sometimes it just doesn't work?
		auto color = Color::Lerp(Palette->ClearWhite, Palette->White, opacity);
		try
		{
			if (SuperNewRoles::ModHelpers::MyRend(player) != nullptr)
			{
				SuperNewRoles::ModHelpers::MyRend(player)->color = color;
			}

			if (SuperNewRoles::ModHelpers::GetSkin(player)->layer != nullptr)
			{
				SuperNewRoles::ModHelpers::GetSkin(player)->layer->color = color;
			}

			if (SuperNewRoles::ModHelpers::HatRend(player) != nullptr)
			{
				SuperNewRoles::ModHelpers::HatRend(player)->color = color;
			}

			if (player->GetPet() == nullptr ? nullptr : player->GetPet().rend != nullptr)
			{
				player->GetPet().rend->color = color;
			}

			if (player->GetPet() == nullptr ? nullptr : player->GetPet().shadowRend != nullptr)
			{
				player->GetPet().shadowRend->color = color;
			}

			if (SuperNewRoles::ModHelpers::VisorSlot(player) != nullptr)
			{
				SuperNewRoles::ModHelpers::VisorSlot(player)->Image->color = color;
			}

			if (player->nameText != nullptr)
			{
				if (opacity == 0.1f)
				{
					SuperNewRoles::ModHelpers::nameText(player)->text = L"";
				}
			}
		}
		catch (...)
		{
		}
	}

	void Scientist::PlayerPhysicsScientist::Postfix(PlayerPhysics *__instance)
	{
		if (AmongUsClient::Instance->GameState != AmongUsClient::GameStates::Started)
		{
			return;
		}
		if (!ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			return;
		}
		if (__instance->myPlayer.isRole(CustomRPC::RoleId::EvilScientist) || __instance->myPlayer.isRole(CustomRPC::RoleId::NiceScientist))
		{
			auto Scientist = __instance->myPlayer;
			if (Scientist == nullptr || Scientist->isDead())
			{
				return;
			}
			auto ison = RoleClass::NiceScientist::IsScientistPlayers.find(__instance->myPlayer.PlayerId) != RoleClass::NiceScientist::IsScientistPlayers.end() && GameData::Instance && RoleClass::NiceScientist::IsScientistPlayers[__instance->myPlayer.PlayerId];
			bool canSee = (__instance->myPlayer.isImpostor() && PlayerControl::LocalPlayer::isImpostor()) || PlayerControl::LocalPlayer::isDead() || !ison;

			auto opacity = canSee ? 0.1f : 0.0f;
			if (ison)
			{
				opacity = std::max(opacity, 0);
				Scientist->MyRend().material.SetFloat(L"_Outline", 0.0f);
			}
			else
			{
				opacity = std::max(opacity, 1.5f);
			}
			setOpacity(Scientist, opacity, canSee);
		}
	}
}
