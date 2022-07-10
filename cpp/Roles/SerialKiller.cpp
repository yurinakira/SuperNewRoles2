#include "SerialKiller.h"
#include "RoleClass.h"
#include "RoleHelper.h"
#include "../TranslateDate.h"
#include "../Helpers/CachedPlayer.h"
#include "../Mode/ModeHandler.h"
#include "../ModHelpers.h"

using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void SerialKiller::SHRFixedUpdate(RoleId role)
	{
		if (!RoleClass::IsMeeting)
		{
			if (AmongUsClient::Instance->AmHost)
			{
				for (auto p : RoleClass::SerialKiller::SerialKillerPlayer)
				{
					if (SuperNewRoles::RoleHelpers::isAlive(p))
					{
						bool IsView;
						std::unordered_map<unsigned char, bool>::const_iterator RoleClass.SerialKiller.IsSuicideViews_iterator = RoleClass.SerialKiller.IsSuicideViews.find(p.PlayerId);
						if (RoleClass::SerialKiller::IsSuicideViews_iterator != RoleClass::SerialKiller::IsSuicideViews.end() && IsView)
						{
							IsView = RoleClass::SerialKiller::IsSuicideViews_iterator->second;
							if (RoleClass::SerialKiller::SuicideTimers.find(p->PlayerId) == RoleClass::SerialKiller::SuicideTimers.end())
							{
								RoleClass::SerialKiller::SuicideTimers[p->PlayerId] = RoleClass::SerialKiller::SuicideDefaultTime;
							}
							RoleClass::SerialKiller::SuicideTimers[p->PlayerId] -= Time::fixedDeltaTime;
							if (RoleClass::SerialKiller::SuicideTimers[p->PlayerId] <= 0)
							{
								p->RpcMurderPlayer(p);
							}
						}
						else
						{
							IsView = RoleClass::SerialKiller::IsSuicideViews_iterator->second;
						}
					}
				}
			}
		}
		if (role == RoleId::SerialKiller)
		{
			if (!RoleClass::IsMeeting && RoleClass::SerialKiller::IsSuicideView)
			{
				RoleClass::SerialKiller::SuicideTime -= Time::fixedDeltaTime;
				RoleClass::SerialKiller::SuicideKillText->text = std::wstring::Format(ModTranslation::getString(L"SerialKillerSuicideText"), (static_cast<int>(RoleClass::SerialKiller::SuicideTime)) + 1);
			}
			else if (RoleClass::SerialKiller::SuicideKillText->text != L"")
			{
				RoleClass::SerialKiller::SuicideKillText->text = L"";
			}
		}
	}

	void SerialKiller::FixedUpdate()
	{
		if (!RoleClass::IsMeeting)
		{
			if (RoleClass::SerialKiller::IsSuicideView)
			{
				RoleClass::SerialKiller::SuicideTime -= Time::fixedDeltaTime;
				if (RoleClass::SerialKiller::SuicideTime <= 0)
				{
					MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::RPCMurderPlayer), SendOption::Reliable, -1);
					writer->Write(CachedPlayer::LocalPlayer->PlayerId);
					writer->Write(CachedPlayer::LocalPlayer->PlayerId);
					writer->Write(std::numeric_limits<unsigned char>::max());
					AmongUsClient::Instance->FinishRpcImmediately(writer);
					RPCProcedure::RPCMurderPlayer(CachedPlayer::LocalPlayer->PlayerId, CachedPlayer::LocalPlayer->PlayerId, std::numeric_limits<unsigned char>::max());
				}
			}
		}
		if (!RoleClass::IsMeeting && RoleClass::SerialKiller::IsSuicideView)
		{
			RoleClass::SerialKiller::SuicideKillText->text = std::wstring::Format(ModTranslation::getString(L"SerialKillerSuicideText"), (static_cast<int>(RoleClass::SerialKiller::SuicideTime)) + 1);
		}
		else
		{
			if (RoleClass::SerialKiller::SuicideKillText->text != L"")
			{
				RoleClass::SerialKiller::SuicideKillText->text = L"";
			}
		}
	}

	void SerialKiller::MurderPlayer(PlayerControl *__instance, PlayerControl *target)
	{
		if (SuperNewRoles::RoleHelpers::isRole(__instance, RoleId::SerialKiller))
		{
			if (__instance->PlayerId == CachedPlayer::LocalPlayer->PlayerId)
			{
				RoleClass::SerialKiller::SuicideTime = RoleClass::SerialKiller::SuicideDefaultTime;
				RoleClass::SerialKiller::IsSuicideView = true;
			}
			RoleClass::SerialKiller::IsSuicideViews[__instance->PlayerId] = true;
			if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
			{
				RoleClass::SerialKiller::SuicideTimers[__instance->PlayerId] = RoleClass::SerialKiller::SuicideDefaultTime;
			}
			else if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
			{
				if (__instance->PlayerId == CachedPlayer::LocalPlayer->PlayerId)
				{
					SuperNewRoles::ModHelpers::SetKillTimerUnchecked(__instance, RoleClass::SerialKiller::KillTime);
					RoleClass::SerialKiller::SuicideTime = RoleClass::SerialKiller::SuicideDefaultTime;
				}
			}
		}
	}

	void SerialKiller::WrapUp()
	{
		if (RoleClass::SerialKiller::IsMeetingReset)
		{
			RoleClass::SerialKiller::SuicideTime = RoleClass::SerialKiller::SuicideDefaultTime;
			for (auto p : RoleClass::SerialKiller::SerialKillerPlayer)
			{
				if (RoleClass::SerialKiller::SuicideTimers.find(p->PlayerId) != RoleClass::SerialKiller::SuicideTimers.end())
				{
					RoleClass::SerialKiller::SuicideTimers[p->PlayerId] = RoleClass::SerialKiller::SuicideDefaultTime;
				}
			}
		}
	}
}
