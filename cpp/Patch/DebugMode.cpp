#include "DebugMode.h"
#include "../Config.h"
#include "../Main.h"
#include "../BotManager.h"
#include "../CustomOption/CustomOptionDate.h"

using namespace BepInEx;
using namespace BepInEx::Configuration;
using namespace BepInEx::IL2CPP;
using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomOption;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

	void DebugMode::MapConsoleUsePatch::Prefix(MapConsole *__instance)
	{
		if (ConfigRoles::getDebugMode()->Value)
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"[DebugMode]Admin Coordinate(x):" + __instance->transform.position.x);
			SuperNewRolesPlugin::Logger->LogInfo(L"[DebugMode]Admin Coordinate(y):" + __instance->transform.position.y);
			SuperNewRolesPlugin::Logger->LogInfo(L"[DebugMode]Admin Coordinate(Z):" + __instance->transform.position.z);
		}
	}

System::Random *const DebugMode::DebugManager::random = new System::Random(static_cast<int>(DateTime::Now.Ticks));
std::vector<PlayerControl*> DebugMode::DebugManager::bots;
std::vector<LateTask*> DebugMode::DebugManager::LateTask::Tasks;

	bool DebugMode::DebugManager::LateTask::run(float deltaTime)
	{
		timer -= deltaTime;
		if (timer <= 0)
		{
			action();
			return true;
		}
		return false;
	}

	DebugMode::DebugManager::LateTask::LateTask(std::function<void()> action, float time, const std::wstring &name)
	{
		this->action = action;
		this->timer = time;
		this->name = name;
		Tasks.push_back(this);
	}

	void DebugMode::DebugManager::LateTask::Update(float deltaTime)
	{
		auto TasksToRemove = std::vector<LateTask*>();
		std::for_each(Tasks.begin(), Tasks.end(), [&] (task)
		{
			if (task::run(deltaTime))
			{
				TasksToRemove.push_back(task);
			}
		});
		std::for_each(TasksToRemove.begin(), TasksToRemove.end(), [&] (std::any task)
		{
			return Tasks.Remove(task);
		});
	}

	void DebugMode::DebugManager::Postfix(KeyboardJoystick *__instance)
	{
		if (!ConfigRoles::getDebugMode()->Value)
		{
			return;
		}

		// Spawn dummys
		if (Input->GetKeyDown(KeyCode::G))
		{
			PlayerControl *bot = BotManager::Spawn(PlayerControl::LocalPlayer::nameText().text);

			bot->NetTransform.SnapTo(PlayerControl::LocalPlayer::transform::position);
			//new LateTask(() => bot.NetTransform.RpcSnapTo(new Vector2(0, 15)), 0.2f, "Bot TP Task");
			//new LateTask(() => { foreach (var pc in CachedPlayer.AllPlayers) pc.PlayerControl.RpcMurderPlayer(bot); }, 0.4f, "Bot Kill Task");
			//new LateTask(() => bot.Despawn(), 0.6f, "Bot Despawn Task");
		}
		/*
		if (Input.GetKeyDown(KeyCode.I))
		{
		    foreach (PlayerControl p in CachedPlayer.AllPlayers)
		    {
		        if (p == PlayerControl.LocalPlayer) continue;
		        MessageWriter writer = AmongUsClient.Instance.StartRpcImmediately(PlayerControl.LocalPlayer.MyPhysics.NetId, (byte)RpcCalls.EnterVent, SendOption.None, p.getClientId());
		        writer.WritePacked(MapUtilities.CachedShipStatus.AllVents[0].Id);
		        AmongUsClient.Instance.FinishRpcImmediately(writer);
		        SuperNewRolesPlugin.Logger.LogInfo(MapUtilities.CachedShipStatus.AllVents[0].transform);
		    }
		}
	
		    if (Input.GetKeyDown(KeyCode.C))
		    {
		        SuperNewRolesPlugin.Logger.LogInfo("CHANGE!!!");
		        foreach (PlayerControl p in CachedPlayer.AllPlayers)
		        {
		            RoleManager.Instance.SetRole(p, RoleTypes.Engineer);
		            AmongUsClient.Instance.Spawn(GameData.Instance, -2, SpawnFlags.IsClientCharacter);
		            AmongUsClient.Instance.Spawn(p, p.OwnerId, SpawnFlags.IsClientCharacter);
		        }
		    }
		    */

		if (Input->GetKeyDown(KeyCode::F10))
		{
			BotManager::Spawn(StringHelper::formatSimple(L"bot{0}", static_cast<unsigned char>(GameData::Instance->GetAvailableId())));
		}
		if (Input->GetKeyDown(KeyCode::F11))
		{
			BotManager::AllBotDespawn();
		}
	}

	std::wstring DebugMode::DebugManager::RandomString(int length)
	{
		const std::wstring chars = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		return std::wstring(Enumerable::Repeat(chars, length).Select([&] (std::any s)
		{
			s[random->Next(s->Length)];
		})->ToArray());
	}

	bool DebugMode::IsDebugMode()
	{
		auto IsDebugModeBool = false;
		if (ConfigRoles::getDebugMode()->Value)
		{
			if (CustomOptions::IsDebugMode->getBool())
			{
				IsDebugModeBool = true;
			}
		}
		return IsDebugModeBool;
	}
}
