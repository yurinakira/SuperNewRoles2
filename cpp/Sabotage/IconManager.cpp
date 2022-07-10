#include "IconManager.h"
#include "../ModHelpers.h"

using namespace UnityEngine;

namespace SuperNewRoles::Sabotage
{

Sprite *IconManager::CognitiveDeficitbuttonSprite;

	Sprite *IconManager::CognitiveDeficitgetButtonSprite()
	{
		if (CognitiveDeficitbuttonSprite)
		{
			return CognitiveDeficitbuttonSprite;
		}
		CognitiveDeficitbuttonSprite = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.CognitiveDeficitButton.png", 115.0f);
		return CognitiveDeficitbuttonSprite;
	}
}
