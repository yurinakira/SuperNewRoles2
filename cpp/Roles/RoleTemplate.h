#pragma once

#include "../CustomRPC/CustomRPC.h"
#include <vector>
#include <type_traits>

using namespace HarmonyLib;
namespace SuperNewRoles::Roles
{
	class RoleTemplate
	{
	public:
		class Role
		{
		public:
			static std::vector<Role*> allRoles;
			PlayerControl *player;
			CustomRPC::RoleId roleId = static_cast<CustomRPC::RoleId>(0);

			virtual void OnMeetingStart() = 0;
			virtual void OnMeetingEnd() = 0;
			virtual void FixedUpdate() = 0;
			virtual void OnKill(PlayerControl *target) = 0;
			virtual void OnDeath(PlayerControl *killer = nullptr) = 0;
			virtual void HandleDisconnect(PlayerControl *player, DisconnectReasons *reason) = 0;
			virtual ~Role()
			{
				delete player;
			}

			virtual void ResetRole();

			static void ClearAll();
		};
	public:
		template<typename T>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] public abstract class RoleBase<T> : Role where T : RoleBase<T>, new()
		class RoleBase : public Role
		{
		static_assert(std::is_base_of<RoleBase<T>, T>::value && std::is_default_constructible<T>::value, L"T must inherit from RoleBase<T> and requires default-constructible elements");
		public:
			static std::vector<T> players;
			static CustomRPC::RoleId RoleType;

			void Init(PlayerControl *player)
			{
				this->player = player;
				players.push_back(static_cast<T>(this));
				allRoles.push_back(this);
			}

			static T getLocal()
			{
				return players.FirstOrDefault([&] (std::any x)
				{
					return x->player == PlayerControl::LocalPlayer;
				});
			}

			static std::vector<PlayerControl*> getAllPlayers()
			{
				return players.Select([&] (std::any x)
				{
					x::player;
				})->ToList();
			}

			static std::vector<PlayerControl*> getLivingPlayers()
			{
				return players.Select([&] (std::any x)
				{
					x::player;
				})->Where([&] (std::any x)
				{
					x::isAlive();
				})->ToList();
			}

			static std::vector<PlayerControl*> getDeadPlayers()
			{
				return players.Select([&] (std::any x)
				{
					x::player;
				})->Where([&] (std::any x)
				{
					return !x::isAlive();
				})->ToList();
			}

			static bool getExists()
			{
				return players.size() > 0;
			}

			static T getRole(PlayerControl *player = nullptr)
			{
				player = (player != nullptr) ? player : PlayerControl::LocalPlayer;
				return players.FirstOrDefault([&] (std::any x)
				{
					return x->player == player;
				});
			}

			static bool isRole(PlayerControl *player)
			{
				return players.Any([&] (std::any x)
				{
					return x->player == player;
				});
			}

			static void setRole(PlayerControl *player)
			{
				if (!isRole(player))
				{
					T role = T();
					role.Init(player);
				}
			}

			static void eraseRole(PlayerControl *player)
			{
				players.DoIf([&] (std::any x)
				{
					return x->player == player;
				}, [&] (std::any x)
				{
					x::ResetRole();
				});
				players.RemoveAll([&] (std::any x)
				{
					return x->player == player && x->roleId == RoleType;
				});
				allRoles.RemoveAll([&] (std::any x)
				{
					return x->player == player && x->roleId == RoleType;
				});
			}

			static void swapRole(PlayerControl *p1, PlayerControl *p2)
			{
				auto index = players.FindIndex([&] (std::any x)
				{
					return x->player == p1;
				});
				if (index >= 0)
				{
					players[index].player = p2;
				}
			}
		};
	};
}
