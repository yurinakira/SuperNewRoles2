#include "RecordsAdminDestroy.h"
#include "../main.h"
#include "../MapCustom.h"

using namespace HarmonyLib;
using namespace UnityEngine;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::MapCustoms
{

	void RecordsAdminDestroy::Postfix()
	{
		if (MapCustom::RecordsAdminDestroy->getBool() && MapCustomHandler::isMapCustom(MapCustomHandler::MapCustomId::Airship))
		{
			//アーカイブのアドミンをSeeyou!
			Transform *Admin = GameObject::Find(L"Airship(Clone)")->transform.FindChild(L"Records").FindChild(L"records_admin_map");
			GameObject::Destroy(Admin->gameObject);
		}
	}
}
