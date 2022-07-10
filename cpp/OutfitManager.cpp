#include "OutfitManager.h"
#include "Main.h"
#include "ModHelpers.h"

namespace SuperNewRoles
{

	void OutfitManager::setOutfit(PlayerControl *pc, GameData::PlayerOutfit *outfit, bool visible)
	{
		pc->Data->Outfits[PlayerOutfitType::Shapeshifted] = outfit;
		pc->CurrentOutfitType = PlayerOutfitType::Shapeshifted;
		SuperNewRolesPlugin::Logger->LogInfo(L"チェンジ");
		pc->RawSetName(outfit->PlayerName);
		pc->RawSetHat(outfit->HatId, outfit->ColorId);
		pc->RawSetVisor(outfit->VisorId);
		pc->RawSetColor(outfit->ColorId);
		ModHelpers::setSkinWithAnim(pc->MyPhysics, outfit->SkinId);

		// idk how to handle pets right now, so just not doing it
		// TODO: FIX PETS
		/*            if (!pc.Data.IsDead)
		            {
		                pc.CurrentPet.Data = HatManager.Instance.GetPetById(outfit.PetId);
		                pc.CurrentPet.transform.position = pc.transform.position;
		                pc.CurrentPet.Source = pc;
		                pc.CurrentPet.Visible = visible;
		                PlayerControl.SetPlayerMaterialColors(outfit.ColorId, pc.CurrentPet.rend);
		            }*/
	}

	void OutfitManager::changeToPlayer(PlayerControl *pc, PlayerControl *target)
	{
		setOutfit(pc, target->Data->DefaultOutfit, target->Visible);
	}

	void OutfitManager::resetChange(PlayerControl *pc)
	{
		changeToPlayer(pc, pc);
		pc->CurrentOutfitType = PlayerOutfitType::Default;
	}
}
