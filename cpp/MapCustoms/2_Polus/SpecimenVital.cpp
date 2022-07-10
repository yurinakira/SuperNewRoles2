#include "SpecimenVital.h"
#include "../main.h"
#include "../MapCustom.h"

using namespace UnityEngine;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::MapCustoms
{

Vector3 *SpecimenVital::pos = new Vector3(35.39f, -22.10f, 1.0f);
bool SpecimenVital::flag = false;

	void SpecimenVital::ClearAndReload()
	{
		flag = false;
	}

	void SpecimenVital::moveVital()
	{
		if (SpecimenVital::flag)
		{
			return;
		}
		if (MapCustomHandler::isMapCustom(MapCustomHandler::MapCustomId::Polus) && MapCustoms::MapCustom::SpecimenVital->getBool())
		{
			auto panel = GameObject::Find(L"panel_vitals");
			if (panel != nullptr)
			{
				auto transform = panel->GetComponent<Transform*>();
				transform->SetPositionAndRotation(SpecimenVital::pos, transform->rotation);
				SpecimenVital::flag = true;
			}
		}
	}
}
