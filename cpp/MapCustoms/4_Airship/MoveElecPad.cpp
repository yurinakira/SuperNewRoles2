#include "MoveElecPad.h"
#include "../2_Polus/SpecimenVital.h"
#include "../main.h"
#include "../MapCustom.h"

using namespace UnityEngine;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::MapCustoms
{

Vector3 *MoveElecPad::Meetpos = new Vector3(16.908f, 14.7988f, 1.0f);
Vector3 *MoveElecPad::Safepos = new Vector3(37.0477f, -3.6707f, 1.0f);
bool MoveElecPad::flag = false;

	void MoveElecPad::ClearAndReload()
	{
		flag = false;
	}

	void MoveElecPad::MoveElecPads()
	{
		if (SpecimenVital::flag)
		{
			return;
		}
		if (MapCustomHandler::isMapCustom(MapCustomHandler::MapCustomId::Airship) && MapCustom::MoveElecPad->getBool())
		{
			auto gap = GameObject::Find(L"task_lightssabotage (gap)"); //昇降機配電盤
			auto cargo = GameObject::Find(L"task_lightssabotage (cargo)"); //貨物室配電盤
			if (gap != nullptr)
			{
				auto transform = gap->GetComponent<Transform*>();
				transform->SetPositionAndRotation(Meetpos, transform->rotation);
				SpecimenVital::flag = true;
			}
			if (cargo != nullptr)
			{
				auto transform = cargo->GetComponent<Transform*>();
				transform->SetPositionAndRotation(Safepos, transform->rotation);
				SpecimenVital::flag = true;
			}
		}
	}
}
