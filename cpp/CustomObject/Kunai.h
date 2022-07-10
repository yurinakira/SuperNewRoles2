#pragma once

using namespace UnityEngine;

namespace SuperNewRoles::CustomObject
{
	class Kunai
	{
	public:
		SpriteRenderer *image;
		GameObject *kunai;

	private:
		static Sprite *sprite;
	public:
		virtual ~Kunai()
		{
			delete image;
			delete kunai;
		}

		static Sprite *getSprite();

		Kunai();
	};
}
