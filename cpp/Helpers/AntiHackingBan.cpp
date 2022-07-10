#include "AntiHackingBan.h"
#include "../CustomRPC/CustomRPC.h"
#include "FastDestroyableSingleton.h"

using namespace Assets::CoreScripts;
using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Helpers
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] ref string skinId)
	bool AntiHackingBan::Setcolorskin::Prefix(PlayerControl *__instance, std::wstring &skinId)
	{
		if (AmongUsClient::Instance->AmClient)
		{
			int valueOrDefault = (__instance->Data == nullptr ? nullptr : (__instance->Data->DefaultOutfit == nullptr ? nullptr : __instance->Data->DefaultOutfit.ColorId)).GetValueOrDefault();
			__instance->SetSkin(skinId, valueOrDefault);
		}
		MessageWriter *obj = AmongUsClient::Instance->StartRpc(__instance->NetId, 40, SendOption::None);
		obj->Write(skinId);
		obj->EndMessage();
		return false;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] ref string hatId)
	bool AntiHackingBan::Sethat::Prefix(PlayerControl *__instance, std::wstring &hatId)
	{
		if (AmongUsClient::Instance->AmClient)
		{
			int valueOrDefault = (__instance->Data == nullptr ? nullptr : (__instance->Data->DefaultOutfit == nullptr ? nullptr : __instance->Data->DefaultOutfit.ColorId)).GetValueOrDefault();
			__instance->SetHat(hatId, valueOrDefault);
		}
		MessageWriter *obj = AmongUsClient::Instance->StartRpc(__instance->NetId, 39, SendOption::None);
		obj->Write(hatId);
		obj->EndMessage();
		return false;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] ref string visorId)
	bool AntiHackingBan::SetVisor::Prefix(PlayerControl *__instance, std::wstring &visorId)
	{
		if (AmongUsClient::Instance->AmClient)
		{
			__instance->SetVisor(visorId);
		}
		MessageWriter *obj = AmongUsClient::Instance->StartRpc(__instance->NetId, 42, SendOption::None);
		obj->Write(visorId);
		obj->EndMessage();
		return false;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] ref string petId)
	bool AntiHackingBan::SetPet::Prefix(PlayerControl *__instance, std::wstring &petId)
	{
		if (AmongUsClient::Instance->AmClient)
		{
			__instance->SetPet(petId);
		}
		MessageWriter *obj = AmongUsClient::Instance->StartRpc(__instance->NetId, 41, SendOption::None);
		obj->Write(petId);
		obj->EndMessage();
		return false;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target, [HarmonyArgument(1)] bool shouldAnimate)
	bool AntiHackingBan::RpcShapeShiftPatch::Prefix(PlayerControl *__instance, PlayerControl *target, bool shouldAnimate)
	{
		if (AmongUsClient::Instance->AmClient)
		{
			__instance->Shapeshift(target, shouldAnimate);
		}
		MessageWriter *val = AmongUsClient::Instance->StartRpcImmediately(__instance->NetId, 46, SendOption::None);
		val->WriteNetObject(target);
		val->Write(shouldAnimate);
		AmongUsClient::Instance->FinishRpcImmediately(val);
		return false;
	}

	bool AntiHackingBan::RpcMurderPlayer::Prefix(PlayerControl *__instance, PlayerControl *target)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::RPCMurderPlayer), Hazel::SendOption::Reliable, -1);
			writer->Write(__instance->PlayerId);
			writer->Write(target->PlayerId);
			writer->Write(std::numeric_limits<unsigned char>::max());
			AmongUsClient::Instance->FinishRpcImmediately(writer);
			RPCProcedure::RPCMurderPlayer(__instance->PlayerId, target->PlayerId, std::numeric_limits<unsigned char>::max());
			return false;
		}
		return true;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, ref bool __result, [HarmonyArgument(0)] string chatText)
	bool AntiHackingBan::RpcSendChatPatch::Prefix(PlayerControl *__instance, bool &__result, const std::wstring &chatText)
	{
		//chatText = Regex.Replace(chatText, "<.*?>", string.Empty);
		if (StringHelper::isEmptyOrWhiteSpace(chatText))
		{
			__result = false;
			return false;
		}
		if (AmongUsClient::Instance->AmClient && FastDestroyableSingleton<HudManager*>::getInstance())
		{
			FastDestroyableSingleton<HudManager*>::getInstance().Chat::AddChat(__instance, chatText);
		}
		if (chatText.find(L"who", StringComparison::OrdinalIgnoreCase) != std::wstring::npos)
		{
			DestroyableSingleton<Telemetry*>::Instance->SendWho();
		}
		MessageWriter *obj = AmongUsClient::Instance->StartRpc(__instance->NetId, 13, SendOption::None);
		obj->Write(chatText);
		obj->EndMessage();
		__result = true;
		return false;
	}
}
