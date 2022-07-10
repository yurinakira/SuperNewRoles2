#pragma once

//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "Lighter.h"
#include "Sheriff.h"
#include "Jackal.h"
#include "Teleporter.h"
#include "SpeedBooster.h"
#include "EvilSpeedBooster.h"
#include "Doorr.h"
#include "Shielder.h"
#include "Freezer.h"
#include "Speeder.h"
#include "Vulture.h"
#include "../CustomObject/Arrow.h"
#include "Clergyman.h"
#include "Bait.h"
#include "Moving.h"
#include "EvilGambler.h"
#include "Bestfalsecharge.h"
#include "Researcher.h"
#include "SelfBomber.h"
#include "JackalFriends.h"
#include "Doctor.h"
#include "CountChanger.h"
#include "Pursuer.h"
#include "Minimalist.h"
#include "Hawk.h"
#include "EvilEraser.h"
#include "Workperson.h"
#include "SerialKiller.h"
#include "Levelinger.h"
#include "MadMayor.h"
#include "NiceHawk.h"
#include "Bakery.h"
#include "MadHawk.h"
#include "MadJester.h"
#include "FalseCharges.h"
#include "NiceTeleporter.h"
#include "Vampire.h"
#include "Fox.h"
#include "DarkKiller.h"
#include "Seer.h"
#include "MadSeer.h"
#include "TeleportingJackal.h"
#include "Demon.h"
#include "SeerFriends.h"
#include "JackalSeer.h"
#include "Assassin.h"
#include "../Patch/DeadPlayer.h"
#include "Arsonist.h"
#include "Samurai.h"
#include "PositionSwapper.h"
#include "Tuna.h"
#include "Mafia.h"
#include "BlackCat.h"
#include "SecretlyKiller.h"
#include "Spy.h"
#include "Kunoichi.h"
#include "../CustomObject/Kunai.h"
#include "DoubleKiller.h"
#include "Smasher.h"
#include "Lovers.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include "../stringhelper.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomObject;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Sabotage;
using namespace TMPro;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] public static class RoleClass
	class RoleClass final
	{
	public:
		static bool IsMeeting;
		static bool IsCoolTimeSetted;
		static System::Random *rnd;
		static Color *ImpostorRed;
		static Color *CrewmateWhite;
		static Color *FoxPurple;
		static bool IsStart;

		static void ClearAndReloadRoles();
		static void NotRole();
	public:
		class SoothSayer final
		{
		public:
			static std::vector<PlayerControl*> SoothSayerPlayer;
			static std::vector<unsigned char> DisplayedPlayer;
			static bool DisplayMode;
			static int Count;
			static Color32 *color;
		private:
			static Sprite *buttonSprite;
		public:
			static Sprite *getButtonSprite();
			static void ClearAndReload();
		};
	public:
		class Jester final
		{
		public:
			static std::vector<PlayerControl*> JesterPlayer;
			static bool IsJesterWin;
			static Color32 *color;
			static bool IsUseVent;
			static bool IsUseSabo;
			static bool IsJesterTaskClearWin;
			static void ClearAndReload();
		};
	public:
		class Lighter final
		{
		public:
			static std::vector<PlayerControl*> LighterPlayer;
			static Color32 *color;
			static float CoolTime;
			static float DurationTime;
			static bool IsLightOn;
			static float UpVision;
			static float DefaultCrewVision;
			static DateTime ButtonTimer;

		private:
			static Sprite *buttonSprite;
		public:
			static Sprite *getButtonSprite();
			static void ClearAndReload();
		};
	public:
		class EvilLighter final
		{
		public:
			static std::vector<PlayerControl*> EvilLighterPlayer;
			static Color32 *color;
			//public static float CoolTime;
			//public static float DurationTime;

			static void ClearAndReload();
		};
	public:
		class EvilScientist final
		{
		public:
			static std::vector<PlayerControl*> EvilScientistPlayer;
			static Color32 *color;
			static float CoolTime;
			static float DurationTime;
		private:
			static Sprite *buttonSprite;
		public:
			static Sprite *getButtonSprite();
			static void ClearAndReload();
		};
	public:
		class Sheriff final
		{
		public:
			static std::vector<PlayerControl*> SheriffPlayer;
			static Color32 *color;
			static PlayerControl *currentTarget;
			static float CoolTime;
			static bool IsNeutralKill;
			static bool IsLoversKill;
			static bool IsMadRoleKill;
			static bool MadRoleKill;
			static float KillMaxCount;
			static std::unordered_map<int, int> KillCount;
			static DateTime ButtonTimer;

		private:
			static Sprite *buttonSprite;

		public:
			static Sprite *getButtonSprite();

			static void ClearAndReload();

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
