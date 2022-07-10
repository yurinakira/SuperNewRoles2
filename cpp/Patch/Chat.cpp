#include "Chat.h"
#include "../Helpers/CachedPlayer.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Roles/RoleHelper.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;

namespace SuperNewRoles::Patch
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(ChatBubble __instance, [HarmonyArgument(0)] string playerName)
	void Chat::SetBubbleName::Postfix(ChatBubble *__instance, const std::wstring &playerName)
	{
		//チャット欄でImpostor陣営から見たSpyがばれないように
		PlayerControl *sourcePlayer = CachedPlayer::AllPlayers.ToArray()->ToList()->FirstOrDefault([&] (std::any x)
		{
			return x::Data->PlayerName->Equals(playerName);
		});
		if (sourcePlayer != nullptr && SuperNewRoles::RoleHelpers::isImpostor(CachedPlayer::LocalPlayer->PlayerControl) && SuperNewRoles::RoleHelpers::isRole(sourcePlayer, std::vector<SuperNewRoles::CustomRPC::RoleId> {RoleId::Egoist, RoleId::Spy}))
		{
			__instance->NameText->color = Palette->ImpostorRed;
		}
	}
}
