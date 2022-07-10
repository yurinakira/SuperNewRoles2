#pragma once

#include <unordered_map>

using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics::ShareCosmetics
{
	class ShareNamePlate
	{
	public:
		static std::unordered_map<int, Sprite*> NamePlateSprites;
	};
}
