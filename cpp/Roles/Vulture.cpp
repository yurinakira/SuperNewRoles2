#include "Vulture.h"
#include "RoleClass.h"
#include "../CustomObject/Arrow.h"
#include "../Helpers/CachedPlayer.h"

using namespace SuperNewRoles::CustomObject;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

std::vector<DeadBody*> Vulture::Targets;

	void Vulture::FixedUpdate::Postfix()
	{
		if (RoleClass::Vulture::Arrow == nullptr)
		{
			Arrow *arrow = new Arrow(RoleClass::Vulture::color);
			arrow->arrow->SetActive(true);
			RoleClass::Vulture::Arrow = arrow;

//C# TO C++ CONVERTER TODO TASK: A 'delete arrow' statement was not added since arrow was assigned to a field. Handle memory management manually.
		}
		float min_target_distance = std::numeric_limits<float>::max();
		DeadBody *target = nullptr;
		std::vector<DeadBody*> deadBodies = UnityEngine::Object::FindObjectsOfType<DeadBody*>();
		for (auto db : deadBodies)
		{
			if (db == nullptr)
			{
				RoleClass::Vulture::Arrow->arrow->SetActive(false);
			}
			float target_distance = Vector3::Distance(CachedPlayer::LocalPlayer->transform->position, db->transform.position);

			if (target_distance < min_target_distance)
			{
				min_target_distance = target_distance;
				target = db;
			}
		}
		if (RoleClass::Vulture::Arrow != nullptr)
		{
			RoleClass::Vulture::Arrow->Update(target->transform.position, RoleClass::Vulture::color);
		}
		if (!PlayerControl::LocalPlayer::isAlive())
		{
			UnityEngine::Object::Destroy(RoleClass::Vulture::Arrow->arrow);
			return;
		}
	}
}
