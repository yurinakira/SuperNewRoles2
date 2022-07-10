#include "LoadTex.h"

using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics
{

LoadTex::LoadImageDelegate LoadTex::LoadImage;

	Sprite *LoadTex::loadSprite(const std::wstring &path)
	{
		//画像サイズは150*150
		if (LoadImage == nullptr)
		{
			LoadImage = IL2CPP::ResolveICall<LoadImageDelegate>(L"UnityEngine.ImageConversion::LoadImage");
		}
		if (LoadImage == nullptr)
		{
			return nullptr;
		}
		try
		{
			std::vector<unsigned char> bytes = File::ReadAllBytes(path);
			Texture2D *texture = new Texture2D(2, 2);
			auto Array = static_cast<Il2CppStructArray<unsigned char>*>(bytes);
			LoadImage->Invoke(texture->Pointer, Array->Pointer, false);

			Rect *rect = new Rect(0.0f, 0.0f, texture->width, texture->height);
			Vector2 tempVar(0.5f, 0.5f);
			return Sprite::Create(texture, rect, &tempVar, 115.0f);

			delete rect;
			delete texture;
		}
		catch (...)
		{
		}
		return nullptr;
	}
}
