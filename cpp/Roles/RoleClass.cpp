//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "RoleClass.h"
#include "../AllRoleSetClass.h"
#include "../LateTask.h"
#include "../BotManager.h"
#include "../Patch/LadderDead.h"
#include "../Map/main.h"
#include "../Sabotage/SabotageManager.h"
#include "Madmate.h"
#include "../Mode/BattleRoyal/main.h"
#include "../EndGame/FinalStatus.h"
#include "../Mode/ModeHandler.h"
#include "../MapCustoms/00_AllMaps/AdditionalVent.h"
#include "../MapCustoms/2_Polus/SpecimenVital.h"
#include "../MapCustoms/4_Airship/MoveElecPad.h"
#include "../Helpers/CachedPlayer.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "RoleHelper.h"
#include "../CustomRPC/CustomRPC.h"
#include "../CustomOption/CustomOptionModel.h"
#include "../MapOptions/MapOption.h"
#include "../ChacheManager/main.h"
#include "../ModHelpers.h"
#include "../CustomOption/CustomOptionDate.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomObject;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Sabotage;
using namespace TMPro;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

bool RoleClass::IsMeeting = false;
bool RoleClass::IsCoolTimeSetted = false;
System::Random *RoleClass::rnd = new System::Random(static_cast<int>(DateTime::Now.Ticks));
Color *RoleClass::ImpostorRed = Palette->ImpostorRed;
Color *RoleClass::CrewmateWhite = Color::white;
Color *RoleClass::FoxPurple = Palette->Purple;
bool RoleClass::IsStart = false;

	void RoleClass::ClearAndReloadRoles()
	{
		AllRoleSetClass::Assigned = false;
		LateTask::Tasks = std::vector<LateTask*>();
		LateTask::AddTasks = std::vector<LateTask*>();
		BotManager::AllBots = std::vector<PlayerControl*>();
		IsMeeting = false;
		IsCoolTimeSetted = false;
		IsStart = false;
		LadderDead::Reset();
		Map::Data::ClearAndReloads();
		SabotageManager::ClearAndReloads();
		Madmate::CheckedImpostor = std::vector<unsigned char>();
		Roles->MadMayor::CheckedImpostor = std::vector<unsigned char>();
		Roles->MadSeer::CheckedImpostor = std::vector<unsigned char>();
		Roles->JackalFriends::CheckedJackal = std::vector<unsigned char>();
		Mode::BattleRoyal::main::VentData = std::unordered_map<unsigned char, std::optional<int>>();
		EndGame::FinalStatusPatch::FinalStatusData::ClearFinalStatusData();
		Mode::ModeHandler::ClearAndReload();
		MapCustoms::AdditionalVents::ClearAndReload();
		MapCustoms::SpecimenVital::ClearAndReload();
		MapCustoms::MoveElecPad::ClearAndReload();
		SoothSayer::ClearAndReload();
		Jester::ClearAndReload();
		Lighter::ClearAndReload();
		EvilLighter::ClearAndReload();
		EvilScientist::ClearAndReload();
		Sheriff::ClearAndReload();
		MeetingSheriff::ClearAndReload();
		Jackal::ClearAndReload();
		Teleporter::ClearAndReload();
		SpiritMedium::ClearAndReload();
		SpeedBooster::ClearAndReload();
		EvilSpeedBooster::ClearAndReload();
		Tasker::ClearAndReload();
		Doorr::ClearAndReload();
		EvilDoorr::ClearAndReload();
		Shielder::ClearAndReload();
		Speeder::ClearAndReload();
		Freezer::ClearAndReload();
		Guesser::ClearAndReload();
		EvilGuesser::ClearAndReload();
		Vulture::ClearAndReload();
		NiceScientist::ClearAndReload();
		Clergyman::ClearAndReload();
		MadMate::ClearAndReload();
		Bait::ClearAndReload();
		HomeSecurityGuard::ClearAndReload();
		StuntMan::ClearAndReload();
		Moving::ClearAndReload();
		Opportunist::ClearAndReload();
		NiceGambler::ClearAndReload();
		EvilGambler::ClearAndReload();
		Bestfalsecharge::ClearAndReload();
		Researcher::ClearAndReload();
		SelfBomber::ClearAndReload();
		God::ClearAndReload();
		AllCleaner::ClearAndReload();
		NiceNekomata::ClearAndReload();
		EvilNekomata::ClearAndReload();
		JackalFriends::ClearAndReload();
		Doctor::ClearAndReload();
		CountChanger::ClearAndReload();
		Pursuer::ClearAndReload();
		Minimalist::ClearAndReload();
		Hawk::ClearAndReload();
		Egoist::ClearAndReload();
		NiceRedRidingHood::ClearAndReload();
		EvilEraser::ClearAndReload();
		Workperson::ClearAndReload();
		Magaziner::ClearAndReload();
		Mayor::ClearAndReload();
		truelover::ClearAndReload();
		Technician::ClearAndReload();
		SerialKiller::ClearAndReload();
		OverKiller::ClearAndReload();
		Levelinger::ClearAndReload();
		EvilMoving::ClearAndReload();
		Amnesiac::ClearAndReload();
		SideKiller::ClearAndReload();
		Survivor::ClearAndReload();
		MadMayor::ClearAndReload();
		NiceHawk::ClearAndReload();
		Bakery::ClearAndReload();
		MadStuntMan::ClearAndReload();
		MadHawk::ClearAndReload();

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
