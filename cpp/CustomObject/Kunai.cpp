#include "Kunai.h"
#include "../ModHelpers.h"

using namespace UnityEngine;

namespace SuperNewRoles::CustomObject
{

Sprite *Kunai::sprite;

	Sprite *Kunai::getSprite()
	{
		if (sprite)
		{
			return sprite;
		}
		sprite = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.KunoichiKunai.png", 200.0f);
		return sprite;
	}

	Kunai::Kunai()
	{
		kunai = new GameObject(L"Kunai");
		kunai->layer = 5;
		image = kunai->AddComponent<SpriteRenderer*>();
		image->sprite = getSprite();
	}
}
