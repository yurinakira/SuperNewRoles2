//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "Kunoichi.h"
#include "RoleHelper.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "../ModHelpers.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Mode/ModeHandler.h"
#include "Scientist.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomObject;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	PlayerControl *Kunoichi::GetShootPlayer(float shotSize)
	{
		PlayerControl *result = nullptr;
		float num = 7;
		Vector3 *pos;
		Vector3 *mouseDirection = Input->mousePosition - new Vector3(Screen::width / 2, Screen::height / 2);
		auto mouseAngle = Mathf::Atan2(mouseDirection->y, mouseDirection->x);

		for (PlayerControl *player : PlayerControl::AllPlayerControls)
		{
			//自分自身は撃ち抜かれない
			if (player->PlayerId == PlayerControl::LocalPlayer::PlayerId)
			{
				continue;
			}

			if (SuperNewRoles::RoleHelpers::isDead(player))
			{
				continue;
			}

			pos = player->transform.position - PlayerControl::LocalPlayer::transform::position;
			pos = new Vector3(pos->x * MathF::Cos(mouseAngle) + pos->y * MathF::Sin(mouseAngle), pos->y * MathF::Cos(mouseAngle) - pos->x * MathF::Sin(mouseAngle));
			if (std::abs(pos->y) < shotSize && (!(pos->x < 0)) && pos->x < num)
			{
				num = pos->x;
				result = player;
			}
		}

		delete pos;
		return result;
	}

	void Kunoichi::KillButtonClick()
	{
		if (!RoleClass::Kunoichi::Kunai->kunai->active)
		{
			return;
		}
		if (!RoleClass::Kunoichi::HideKunai && RoleClass::NiceScientist::IsScientistPlayers.find(CachedPlayer::LocalPlayer->PlayerId) != RoleClass::NiceScientist::IsScientistPlayers.end() && GameData::Instance && RoleClass::NiceScientist::IsScientistPlayers[CachedPlayer::LocalPlayer->PlayerId])
		{
			return;
		}
		PlayerControl::LocalPlayer::SetKillTimerUnchecked(RoleClass::Kunoichi::KillCoolTime, RoleClass::Kunoichi::KillCoolTime);
		RoleClass::Kunoichi::SendKunai = RoleClass::Kunoichi::Kunai;
		RoleClass::Kunoichi::Kunai = new CustomObject::Kunai();
		RoleClass::Kunoichi::Kunai->kunai->transform->position = CachedPlayer::LocalPlayer->transform->position;
		RoleClass::Kunoichi::KunaiSend = true;
		RoleClass::Kunoichi::Kunais.push_back(RoleClass::Kunoichi::SendKunai);
		// クリックした座標の取得（スクリーン座標からワールド座標に変換）
		Vector3 *mouseWorldPos = Camera->main.ScreenToWorldPoint(Input->mousePosition);

		Vector3 tempVar(1, 1, 0);
		Vector3 *shotForward = Vector3::Scale((mouseWorldPos - RoleClass::Kunoichi::SendKunai->kunai->transform.position), &tempVar).normalized;

		// 弾に速度を与える
		auto body = RoleClass::Kunoichi::SendKunai->kunai->AddComponent<Rigidbody2D*>();
		body->gravityScale = 0.0f;
		body->velocity = shotForward * 10.0f;
	}

	void Kunoichi::Update()
	{
		Vector3 *mouseDirection = Input->mousePosition - new Vector3(Screen::width / 2, Screen::height / 2);
		auto MouseAngle = Mathf::Atan2(mouseDirection->y, mouseDirection->x);
		auto targetPosition = CachedPlayer::LocalPlayer->transform->position + new Vector3(0.8f * static_cast<float>(std::cos(MouseAngle)), 0.8f * static_cast<float>(std::sin(MouseAngle)));
		RoleClass::Kunoichi::Kunai->kunai->transform.position += (targetPosition - RoleClass::Kunoichi::Kunai->kunai->transform.position) * 0.4f;
		RoleClass::Kunoichi::Kunai->image->transform->eulerAngles = new Vector3(0.0f, 0.0f, static_cast<float>(MouseAngle * 360.0f / M_PI / 2.0f));
		if (std::cos(MouseAngle) < 0.0)
		{
			if (RoleClass::Kunoichi::Kunai->image->transform.localScale.y > 0)
			{
				RoleClass::Kunoichi::Kunai->image->transform->localScale = new Vector3(1.0f, -1.0f);
			}
		}
		else
		{
			if (RoleClass::Kunoichi::Kunai->image->transform.localScale.y < 0)
			{
				RoleClass::Kunoichi::Kunai->image->transform->localScale = new Vector3(1.0f, 1.0f);
			}
		}

		if (PlayerControl::LocalPlayer::inVent)
		{
			RoleClass::Kunoichi::Kunai->kunai->active = false;
		}
		for (auto kunai : RoleClass::Kunoichi::Kunais.ToArray())
		{
			if (Vector2::Distance(CachedPlayer::LocalPlayer->transform->position, kunai->kunai->transform.position) > 6.0f)
			{
				GameObject::Destroy(kunai->kunai);
				RoleClass::Kunoichi::Kunais.Remove(kunai);
			}
			else
			{
				auto kunaipos = kunai->kunai->transform.position;
				for (auto p : CachedPlayer::AllPlayers)
				{
					if (SuperNewRoles::RoleHelpers::isDead(p))
					{
						continue;
					}
					if (p->PlayerId == CachedPlayer::LocalPlayer->PlayerId)
					{
						continue;
					}
					Vector2 tempVar(0,0.4f);
					if (Vector2::Distance(p->GetTruePosition() + &tempVar, kunaipos) < 0.4f)
					{
						if (RoleClass::Kunoichi::HitCount.find(PlayerControl::LocalPlayer::PlayerId) == RoleClass::Kunoichi::HitCount.end())
						{
							RoleClass::Kunoichi::HitCount[PlayerControl::LocalPlayer::PlayerId] = std::unordered_map<unsigned char, int>();
						}
						if (RoleClass::Kunoichi::HitCount[PlayerControl::LocalPlayer::PlayerId].find(p->PlayerId) == RoleClass::Kunoichi::HitCount[PlayerControl::LocalPlayer::PlayerId].end())
						{
							RoleClass::Kunoichi::HitCount[PlayerControl::LocalPlayer::PlayerId][p->PlayerId] = 0;
						}
						RoleClass::Kunoichi::HitCount[PlayerControl::LocalPlayer::PlayerId][p->PlayerId]++;
						if (RoleClass::Kunoichi::HitCount[PlayerControl::LocalPlayer::PlayerId][p->PlayerId] >= RoleClass::Kunoichi::KillKunai)
						{
							ModHelpers::checkMuderAttemptAndKill(PlayerControl::LocalPlayer, p, false, false);
							RoleClass::Kunoichi::HitCount[PlayerControl::LocalPlayer::PlayerId][p->PlayerId] = 0;
						}
						RoleClass::Kunoichi::Kunais.Remove(kunai);
						GameObject::Destroy(kunai->kunai);
						break;
					}
				}
			}
		}
		if (RoleClass::Kunoichi::HideTime != -1)
		{
			if (!HudManager::Instance->IsIntroDisplayed)
			{
				if (RoleClass::Kunoichi::OldPosition == CachedPlayer::LocalPlayer->PlayerControl->GetTruePosition())
				{
					RoleClass::Kunoichi::StopTime += Time::fixedDeltaTime;
					if (RoleClass::Kunoichi::StopTime >= RoleClass::Kunoichi::HideTime)
					{
						MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetScientistRPC), Hazel::SendOption::Reliable, -1);
						writer->Write(true);
						writer->Write(CachedPlayer::LocalPlayer->PlayerId);
						AmongUsClient::Instance->FinishRpcImmediately(writer);
						CustomRPC::RPCProcedure::SetScientistRPC(true, CachedPlayer::LocalPlayer->PlayerId);
					}
				}
				else
				{
					if (RoleClass::Kunoichi::StopTime >= RoleClass::Kunoichi::HideTime)
					{
						MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetScientistRPC), Hazel::SendOption::Reliable, -1);
						writer->Write(false);
						writer->Write(CachedPlayer::LocalPlayer->PlayerId);
						AmongUsClient::Instance->FinishRpcImmediately(writer);
						CustomRPC::RPCProcedure::SetScientistRPC(false, CachedPlayer::LocalPlayer->PlayerId);
					}
					RoleClass::Kunoichi::StopTime = 0;
				}
				RoleClass::Kunoichi::OldPosition = CachedPlayer::LocalPlayer->PlayerControl->GetTruePosition();
			}
		}
		/*
		if (RoleClass.Kunoichi.KunaiSend)
		{
		    if (PhysicsHelpers.AnythingBetween(RoleClass.Kunoichi.SendKunai.kunai.transform.position, , Constants.ShipAndObjectsMask, false);)
		    {
		        RoleClass.Kunoichi.SendKunai.kunai.transform.position += new Vector3(0.1f, 0, 0);
		    } else
		    {
		        return;
		    }
		    RoleClass.Kunoichi.SendKunai.kunai.GetComponent<Rigidbody2D>().velocity = new Vector2();
		    RoleClass.Kunoichi.Kunais.Add(RoleClass.Kunoichi.SendKunai);
		    RoleClass.Kunoichi.SendKunai = null;
		    RoleClass.Kunoichi.KunaiSend = false;
		}*/
	}

	void Kunoichi::setOpacity(PlayerControl *player, float opacity, bool cansee)
	{
		// Sometimes it just doesn't work?

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
