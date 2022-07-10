#include "main.h"
#include "../Helpers/CachedPlayer.h"
#include "../Roles/RoleHelper.h"

using namespace SuperNewRoles::CustomRPC;

namespace SuperNewRoles
{

std::unordered_map<int, RoleId> ChacheManager::MyRoleChache;
std::unordered_map<int, RoleId> ChacheManager::MyGhostRoleChache;
std::unordered_map<int, PlayerControl*> ChacheManager::LoversChache;
std::unordered_map<int, PlayerControl*> ChacheManager::QuarreledChache;

	void ChacheManager::Load()
	{
		MyRoleChache = std::unordered_map<int, RoleId>();
		MyGhostRoleChache = std::unordered_map<int, RoleId>();
		LoversChache = std::unordered_map<int, PlayerControl*>();
		QuarreledChache = std::unordered_map<int, PlayerControl*>();
	}

	void ChacheManager::ResetChache()
	{
		ResetQuarreledChache();
		ResetLoversChache();
		ResetMyRoleChache();
		ResetMyGhostRoleChache();
	}

	void ChacheManager::ResetQuarreledChache()
	{
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::RoleHelpers::IsQuarreled(p, false))
			{
				QuarreledChache[p->PlayerId] = SuperNewRoles::RoleHelpers::GetOneSideQuarreled(p, false);
			}
			else
			{
				QuarreledChache[p->PlayerId] = nullptr;
			}
		}
	}

	void ChacheManager::ResetLoversChache()
	{
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::RoleHelpers::IsLovers(p, false))
			{
				LoversChache[p->PlayerId] = SuperNewRoles::RoleHelpers::GetOneSideLovers(p, false);
			}
			else
			{
				LoversChache[p->PlayerId] = nullptr;
			}
		}
	}

	void ChacheManager::ResetMyRoleChache()
	{
		for (auto p : CachedPlayer::AllPlayers)
		{
			MyRoleChache[p->PlayerId] = SuperNewRoles::RoleHelpers::getRole(p, false);
		}
	}

	void ChacheManager::ResetMyGhostRoleChache()
	{
		for (auto p : CachedPlayer::AllPlayers)
		{
			MyGhostRoleChache[p->PlayerId] = SuperNewRoles::RoleHelpers::getGhostRole(p, false);
		}
	}
}
