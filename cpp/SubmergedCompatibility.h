#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <any>
#include <typeinfo>
#include <cstdint>
#include "exceptionhelper.h"

using namespace BepInEx;
using namespace BepInEx::IL2CPP;
using namespace HarmonyLib;
using namespace UnhollowerRuntimeLib;
using namespace UnityEngine;

namespace SuperNewRoles
{
	class SubmergedCompatibility final
	{
	private:
		static SemanticVersioning::Version *Version;
		static bool Loaded;
		static BasePlugin *Plugin;
		static System::Reflection::Assembly *Assembly;
		static std::vector<std::type_info> Types;
		static std::unordered_map<std::wstring, std::type_info> InjectedTypes;

	public:
		class Classes final
		{
		public:
			static const std::wstring ElevatorMover;
		};

	public:
		static const std::wstring SUBMERGED_GUID;
		static constexpr ShipStatus::MapType *SUBMERGED_MAP_TYPE = static_cast<ShipStatus::MapType*>(5);

		virtual ~SubmergedCompatibility()
		{
			delete SUBMERGED_MAP_TYPE;
		}

		static SemanticVersioning::Version *getVersion();
		static void setVersion(SemanticVersioning::Version *value);
		static bool getLoaded();
		static void setLoaded(bool value);
		static BasePlugin *getPlugin();
		static void setPlugin(BasePlugin *value);
		static System::Reflection::Assembly *getAssembly();
		static void setAssembly(System::Reflection::Assembly *value);
		static std::vector<std::type_info> getTypes();
		static void setTypes(const std::vector<std::type_info> &value);
		static std::unordered_map<std::wstring, std::type_info> getInjectedTypes();
		static void setInjectedTypes(const std::unordered_map<std::wstring, std::type_info> &value);

	private:
		static MonoBehaviour *_submarineStatus;
	public:
		static MonoBehaviour *getSubmarineStatus();

		static void setDisableO2MaskCheckForEmergency(bool value);

	private:
		static std::type_info SubmarineStatusType;
		static MethodInfo *CalculateLightRadiusMethod;

		static std::type_info TaskIsEmergencyPatchType;
		static FieldInfo *DisableO2MaskCheckField;

		static MethodInfo *RpcRequestChangeFloorMethod;
		static std::type_info FloorHandlerType;
		static MethodInfo *GetFloorHandlerMethod;
		static FieldInfo *OnUpperField;

		static std::type_info Vent_MoveToVent_PatchType;
		static FieldInfo *InTransitionField;

		static std::type_info CustomTaskTypesType;
		static FieldInfo *RetrieveOxigenMaskField;
	public:
		static TaskTypes *RetrieveOxygenMask;
	private:
		static std::type_info SubmarineOxygenSystemType;
		static FieldInfo *SubmarineOxygenSystemInstanceField;
		static MethodInfo *RepairDamageMethod;


	public:
		static void Initialize();

		static MonoBehaviour *AddSubmergedComponent(GameObject *obj, const std::wstring &typeName);

		static float GetSubmergedNeutralLightRadius(bool isImpostor);

		static void ChangeFloor(bool toUpper);

		static void ChangeFloor(bool toUpper, PlayerControl *player);

		static bool GetFloor();

		static bool GetFloor(PlayerControl *player);

		static bool getInTransition();

		static void RepairOxygen();

		static bool isSubmerged();
	};

	class MissingSubmergedBehaviour : public MonoBehaviour
	{
	private:
		class StaticConstructor
		{
		public:
			StaticConstructor();
		};

	private:
		static MissingSubmergedBehaviour::StaticConstructor staticConstructor;

	public:
		MissingSubmergedBehaviour(std::intptr_t ptr);
	};
}
