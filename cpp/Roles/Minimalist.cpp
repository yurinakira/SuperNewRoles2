#include "Minimalist.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleClass.h"

using namespace SuperNewRoles::CustomRPC;

namespace SuperNewRoles::Roles
{

	void Minimalist::MurderPatch::Postfix(PlayerControl *__instance)
	{
		if (CachedPlayer::LocalPlayer->PlayerId == __instance->PlayerId && PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::Minimalist))
		{
			PlayerControl::LocalPlayer::SetKillTimerUnchecked(RoleClass::Minimalist::KillCoolTime);
		}
	}

	void Minimalist::FixedUpdate::Postfix(RoleId role)
	{
		if (role == RoleId::Minimalist)
		{
			if (!RoleClass::Minimalist::UseVent)
			{
				if (FastDestroyableSingleton<HudManager*>::getInstance().ImpostorVentButton::gameObject::active)
				{
					FastDestroyableSingleton<HudManager*>::getInstance().ImpostorVentButton::gameObject::SetActive(false);
				}
			}
			if (!RoleClass::Minimalist::UseSabo)
			{
				if (FastDestroyableSingleton<HudManager*>::getInstance().SabotageButton::gameObject::active)
				{
					FastDestroyableSingleton<HudManager*>::getInstance().SabotageButton::gameObject::SetActive(false);
				}
			}
			if (!RoleClass::Minimalist::UseReport)
			{
				if (FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::gameObject::active)
				{
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::SetActive(false); //通報
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::gameObject::SetActiveRecursively(false);
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::graphic->enabled = false;
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton->enabled = false;
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::graphic->sprite = nullptr;
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::buttonLabelText->enabled = false;
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::buttonLabelText::SetText(L"");

				}
			}
		}
		else if (role == RoleId::Fox)
		{
			if (!RoleClass::Fox::UseReport)
			{
				if (FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::gameObject::active)
				{
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::SetActive(false); //通報
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::gameObject::SetActiveRecursively(false);
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::graphic->enabled = false;
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton->enabled = false;
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::graphic->sprite = nullptr;
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::buttonLabelText->enabled = false;
					FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::buttonLabelText::SetText(L"");
				}

			}
		}
		else if (role == RoleId::SecretlyKiller)
		{
			HudManager::Instance->KillButton.gameObject.SetActive(false);
			//FastDestroyableSingleton<HudManager>.Instance.KillButton.gameObject.SetActive(false);
		}
		else if (role == RoleId::DoubleKiller)
		{
			//ボタン削除
			if (!RoleClass::DoubleKiller::CanUseSabo)
			{
				if (FastDestroyableSingleton<HudManager*>::getInstance().SabotageButton::gameObject::active)
				{
					FastDestroyableSingleton<HudManager*>::getInstance().SabotageButton::gameObject::SetActive(false);
				}
			}
			if (!RoleClass::DoubleKiller::CanUseVent)
			{
				if (FastDestroyableSingleton<HudManager*>::getInstance().ImpostorVentButton::gameObject::active)
				{
					FastDestroyableSingleton<HudManager*>::getInstance().ImpostorVentButton::gameObject::SetActive(false);
				}
			}
			//純正キルボタン削除
			HudManager::Instance->KillButton.gameObject.SetActive(false);
		}
		else if (role == RoleId::Smasher)
		{
			HudManager::Instance->KillButton.gameObject.SetActive(false);
		}
		else if (role == RoleId::Neet) //ニートのボタン削除
		{
			if (FastDestroyableSingleton<HudManager*>::getInstance().UseButton::gameObject::active) //使うボタンが有効の時
			{
				HudManager::Instance->UseButton.gameObject.SetActive(false); //使うボタンを無効化
			}
			if (FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::gameObject::active)
			{
				FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::SetActive(false); //通報
				FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::gameObject::SetActiveRecursively(false);
				FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::graphic->enabled = false;
				FastDestroyableSingleton<HudManager*>::getInstance().ReportButton->enabled = false;
				FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::graphic->sprite = nullptr;
				FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::buttonLabelText->enabled = false;
				FastDestroyableSingleton<HudManager*>::getInstance().ReportButton::buttonLabelText::SetText(L"");
			}
		}
		else if (role == RoleId::FastMaker && !RoleClass::FastMaker::IsCreatedMadMate) //マッドが作られていないとき
		{
			//純正キルボタン削除
			HudManager::Instance->KillButton.gameObject.SetActive(false);
		}
	}
}
