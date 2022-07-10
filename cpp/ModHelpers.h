#pragma once

//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "Helpers/CachedPlayer.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <any>
#include <typeinfo>
#include <functional>
#include <optional>
#include <cstdint>
#include "exceptionhelper.h"
#include <type_traits>
#include "tangible_filesystem.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Roles;
using namespace TMPro;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles
{
	class ModHelpers final
	{
	public:
		enum class MurderAttemptResult
		{
			PerformKill,
			SuppressKill,
			BlankKill,
			GuardianGuardKill
		};
	public:
		static bool getShowButtons();
		static void SetKillTimerUnchecked(PlayerControl *player, float time, float max = float::NegativeInfinity);

		static Sprite *CreateSprite(const std::wstring &path, bool fromDisk = false);
		static std::optional<unsigned char> GetKey(std::unordered_map<unsigned char, unsigned char> &dec, unsigned char Value);

		static std::vector<GameObject*> GetChildren(GameObject *ParentObject);
		static void DeleteObject(std::vector<Transform*> &trans, const std::wstring &notdelete);
		static void DeleteObject(std::vector<GameObject*> &trans, const std::wstring &notdelete);
		static std::vector<PlayerControl*> getAllNotDisconnectedPlayerControl();
		static void SetActiveAllObject(std::vector<GameObject*> &trans, const std::wstring &notdelete, bool IsActive);
		static void setSkinWithAnim(PlayerPhysics *playerPhysics, const std::wstring &SkinId);
		static std::unordered_map<unsigned char, PlayerControl*> allPlayersById();

		template<typename T>
		static void destroyList(Il2CppSystem::Collections::Generic::List<T> *items)
		{
			static_assert(std::is_base_of<UnityEngine.Object, T>::value, L"T must inherit from UnityEngine.Object");

			if (items == nullptr)
			{
				return;
			}
			for (auto item : *items)
			{
				UnityEngine::Object::Destroy(item);
			}
		}
		template<typename T>
		static void destroyList(std::vector<T> &items)
		{
			static_assert(std::is_base_of<UnityEngine.Object, T>::value, L"T must inherit from UnityEngine.Object");

			if (items.empty())
			{
				return;
			}
			for (auto item : items)
			{
				UnityEngine::Object::Destroy(item);
			}
		}
		static MurderAttemptResult checkMuderAttempt(PlayerControl *killer, PlayerControl *target, bool blockRewind = false);
		static void generateAndAssignTasks(PlayerControl *player, int numCommon, int numShort, int numLong);
		static std::vector<unsigned char> generateTasks(int numCommon, int numShort, int numLong);
	private:
		static float tien;
	public:
		static MurderAttemptResult checkMuderAttemptAndKill(PlayerControl *killer, PlayerControl *target, bool isMeetingStart = false, bool showAnimation = true);
		static void UncheckedMurderPlayer(PlayerControl *killer, PlayerControl *target, bool isMeetingStart = false, bool showAnimation = true);
		static void SetPrivateRole(CachedPlayer *player, RoleTypes *role, CachedPlayer *seer = nullptr);
		static InnerNet::ClientData *getClient(PlayerControl *player);
		static int getClientId(PlayerControl *player);
		static bool hidePlayerName(PlayerControl *source, PlayerControl *target);

		static std::unordered_map<std::wstring, Sprite*> CachedSprites;

		static Sprite *loadSpriteFromResources(const std::wstring &path, float pixelsPerUnit);

		static bool isCustomServer();
		static std::any TryCast(Il2CppObjectBase *self, std::type_info type);
		static std::wstring cs(std::any unityEngine, const std::wstring &v);

		static Texture2D *loadTextureFromResources(const std::wstring &path);

		static std::wstring cs(Color *c, const std::wstring &s);
		template<typename T>
		static T GetRandom(std::vector<T> &list)
		{
			auto indexdate = UnityEngine::Random::Range(0, list.size());
			return list[indexdate];
		}
		static PlayerControl *GetRandompc(std::vector<PlayerControl*> &list);
		template<typename T>
		static int GetRandomIndex(std::vector<T> &list)
		{
			auto indexdate = UnityEngine::Random::Range(0, list.size());
			return indexdate;
		}

		static std::unordered_map<unsigned char, SpriteRenderer*> MyRendCache;
		static std::unordered_map<unsigned char, SkinLayer*> SkinLayerCache;
		static std::unordered_map<unsigned char, HatParent*> HatRendererCache;
		static std::unordered_map<unsigned char, SpriteRenderer*> HatRendCache;
		static std::unordered_map<unsigned char, VisorLayer*> VisorSlotCache;
		static TextMeshPro *nameText(PlayerControl *player);
		static TextMeshPro *nameText(PoolablePlayer *player);
		static SpriteRenderer *MyRend(PlayerControl *player);
		static SpriteRenderer *rend(PlayerPhysics *player);
		static SkinLayer *GetSkin(PlayerControl *player);
		static SkinLayer *GetSkin(PlayerPhysics *player);
		static HatParent *HatRenderer(PlayerControl *player);
		static SpriteRenderer *HatRend(PlayerControl *player);
		static VisorLayer *VisorSlot(PlayerControl *player);

		static HatParent *HatSlot(PoolablePlayer *player);
		static VisorLayer *VisorSlot(PoolablePlayer *player);

		static Texture2D *loadTextureFromDisk(const std::wstring &path);
		using d_LoadImage = std::function<bool (std::intptr_t tex, std::intptr_t data, bool markNonReadable)>;
		static d_LoadImage iCall_LoadImage;
	private:
		static bool LoadImage(Texture2D *tex, std::vector<unsigned char> &data, bool markNonReadable);

	public:
		static PlayerControl *playerById(unsigned char id);

		static bool IsCheckListPlayerControl(std::vector<PlayerControl*> &ListDate, PlayerControl *CheckPlayer);
		static bool IsPosition(Vector3 *pos, Vector2 *pos2);
		static bool IsPositionDistance(Vector2 *pos, Vector2 *pos2, float distance);


//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
