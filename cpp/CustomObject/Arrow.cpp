#include "Arrow.h"
#include "../ModHelpers.h"

using namespace SuperNewRoles;
using namespace UnityEngine;

namespace SuperNewRoles::CustomObject
{

Sprite *Arrow::sprite;

	Sprite *Arrow::getSprite()
	{
		if (sprite)
		{
			return sprite;
		}
		sprite = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.Arrow.png", 200.0f);
		return sprite;
	}

	Arrow::Arrow(Color *color)
	{
		arrow = new GameObject(L"Arrow");
		arrow->layer = 5;
		image = arrow->AddComponent<SpriteRenderer*>();
		image->sprite = getSprite();
		image->color = color;
	}

	void Arrow::Update()
	{
		Vector3 *target = oldTarget;
		if (target == nullptr)
		{
			target = Vector3::zero;
		}
		Update(target);
	}

	void Arrow::Update(Vector3 *target, std::optional<Color*> &color)
	{
		if (arrow == nullptr)
		{
			return;
		}
		oldTarget = target;

		if (color)
		{
			image->color = color.value();
		}

		Camera *main = Camera->main;
		Vector2 *vector = target - main->transform.position;
		float num = vector->magnitude / (main->orthographicSize * perc);
		image->enabled = static_cast<double>(num) > 0.3;
		Vector2 *vector2 = main->WorldToViewportPoint(target);
		if (Between(vector2->x, 0.0f, 1.0f) && Between(vector2->y, 0.0f, 1.0f))
		{
			arrow->transform->position = target - static_cast<Vector3*>(vector->normalized) * 0.6f;
			float num2 = Mathf::Clamp(num, 0.0f, 1.0f);
			arrow->transform->localScale = new Vector3(num2, num2, num2);
		}
		else
		{
			Vector2 *vector3 = new Vector2(Mathf::Clamp(vector2->x * 2.0f - 1.0f, -1.0f, 1.0f), Mathf::Clamp(vector2->y * 2.0f - 1.0f, -1.0f, 1.0f));
			float orthographicSize = main->orthographicSize;
			float num3 = main->orthographicSize * main->aspect;
			Vector3 *vector4 = new Vector3(Mathf::LerpUnclamped(0.0f, num3 * 0.88f, vector3->x), Mathf::LerpUnclamped(0.0f, orthographicSize * 0.79f, vector3->y), 0.0f);
			arrow->transform->position = main->transform.position + vector4;
			arrow->transform->localScale = Vector3::one;

			delete vector4;
			delete vector3;
		}

		LookAt2d(arrow->transform, target);
	}

	void Arrow::LookAt2d(Transform *transform, Vector3 *target)
	{
		Vector3 *vector = target - transform->position;
		vector->Normalize();
		float num = Mathf::Atan2(vector->y, vector->x);
		if (transform->lossyScale.x < 0.0f)
		{
			num += 3.1415927f;
		}
		transform->rotation = Quaternion::Euler(0.0f, 0.0f, num * 57.29578f);
	}

	bool Arrow::Between(float value, float min, float max)
	{
		return value > min && value < max;
	}
}
