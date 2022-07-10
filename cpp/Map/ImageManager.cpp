#include "ImageManager.h"
#include "../ModHelpers.h"

using namespace UnityEngine;

namespace SuperNewRoles::Map
{

Sprite *ImageManager::AgarthaAdminButton;

	Sprite *ImageManager::GetAgarthaAdminButton()
	{
		if (AgarthaAdminButton != nullptr)
		{
			return AgarthaAdminButton;
		}
		AgarthaAdminButton = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.Agartha.AdminButton.png", 115.0f);
		return AgarthaAdminButton;
	}
}
