#pragma once

#include <optional>

using namespace SuperNewRoles;
using namespace UnityEngine;

namespace SuperNewRoles::CustomObject
{
	class Arrow
	{
	public:
		float perc = 0.925f;
		SpriteRenderer *image;
		GameObject *arrow;
	private:
		Vector3 *oldTarget;

		static Sprite *sprite;
	public:
		virtual ~Arrow()
		{
			delete image;
			delete arrow;
			delete oldTarget;
		}

		static Sprite *getSprite();

		Arrow(Color *color);

		void Update();

		void Update(Vector3 *target, std::optional<Color*> &color = std::nullopt);

	private:
		void LookAt2d(Transform *transform, Vector3 *target);

		bool Between(float value, float min, float max);
	};
}
