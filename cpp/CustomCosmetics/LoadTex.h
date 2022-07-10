#pragma once

#include <string>
#include <vector>
#include <cstdint>

using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics
{
	class LoadTex
	{
		using LoadImageDelegate = std::function<bool (std::intptr_t tex, std::intptr_t data, bool markNonReadable)>;
		using EncodeImageDelegate = std::function<Il2CppStructArray<unsigned char> *(std::intptr_t tex)>;
	public:
		static LoadImageDelegate LoadImage;
		static Sprite *loadSprite(const std::wstring &path);
	};
}
