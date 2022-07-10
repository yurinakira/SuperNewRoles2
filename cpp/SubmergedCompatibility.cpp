//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "SubmergedCompatibility.h"
#include "Helpers/MapUtilities.h"
#include "Main.h"

using namespace BepInEx;
using namespace BepInEx::IL2CPP;
using namespace HarmonyLib;
using namespace UnhollowerRuntimeLib;
using namespace UnityEngine;

namespace SuperNewRoles
{

SemanticVersioning::Version *SubmergedCompatibility::Version;
bool SubmergedCompatibility::Loaded = false;
BasePlugin *SubmergedCompatibility::Plugin;
System::Reflection::Assembly *SubmergedCompatibility::Assembly;
std::vector<std::type_info> SubmergedCompatibility::Types;
std::unordered_map<std::wstring, std::type_info> SubmergedCompatibility::InjectedTypes;
const std::wstring SubmergedCompatibility::Classes::ElevatorMover = L"ElevatorMover";
const std::wstring SubmergedCompatibility::SUBMERGED_GUID = L"Submerged";

	SemanticVersioning::Version *SubmergedCompatibility::getVersion()
	{
		return Version;
	}

	void SubmergedCompatibility::setVersion(SemanticVersioning::Version *value)
	{
		Version = value;
	}

	bool SubmergedCompatibility::getLoaded()
	{
		return Loaded;
	}

	void SubmergedCompatibility::setLoaded(bool value)
	{
		Loaded = value;
	}

	BasePlugin *SubmergedCompatibility::getPlugin()
	{
		return Plugin;
	}

	void SubmergedCompatibility::setPlugin(BasePlugin *value)
	{
		Plugin = value;
	}

	System::Reflection::Assembly *SubmergedCompatibility::getAssembly()
	{
		return Assembly;
	}

	void SubmergedCompatibility::setAssembly(System::Reflection::Assembly *value)
	{
		Assembly = value;
	}

	std::vector<std::type_info> SubmergedCompatibility::getTypes()
	{
		return Types;
	}

	void SubmergedCompatibility::setTypes(const std::vector<std::type_info> &value)
	{
		Types = value;
	}

	std::unordered_map<std::wstring, std::type_info> SubmergedCompatibility::getInjectedTypes()
	{
		return InjectedTypes;
	}

	void SubmergedCompatibility::setInjectedTypes(const std::unordered_map<std::wstring, std::type_info> &value)
	{
		InjectedTypes = value;
	}

MonoBehaviour *SubmergedCompatibility::_submarineStatus;

	MonoBehaviour *SubmergedCompatibility::getSubmarineStatus()
	{
		if (!getLoaded())
		{
			return nullptr;
		}

		if (_submarineStatus == nullptr || _submarineStatus->WasCollected || !_submarineStatus || _submarineStatus == nullptr)
		{
			if (MapUtilities::CachedShipStatus == nullptr || MapUtilities::CachedShipStatus->WasCollected || !MapUtilities::CachedShipStatus || MapUtilities::CachedShipStatus == nullptr)
			{
				return _submarineStatus = nullptr;
			}
			else
			{
				if (MapUtilities::CachedShipStatus->Type == SUBMERGED_MAP_TYPE)
				{
					return _submarineStatus = MapUtilities::CachedShipStatus->GetComponent(Il2CppType::From(SubmarineStatusType)) == nullptr ? nullptr : dynamic_cast<MonoBehaviour*>(MapUtilities::CachedShipStatus->GetComponent(Il2CppType::From(SubmarineStatusType))->TryCast(SubmarineStatusType));
				}
				else
				{
					return _submarineStatus = nullptr;
				}
			}
		}
		else
		{
			return _submarineStatus;
		}
	}

	void SubmergedCompatibility::setDisableO2MaskCheckForEmergency(bool value)
	{
		if (!getLoaded())
		{
			return;
		}
		DisableO2MaskCheckField->SetValue(std::any(), value);
	}

std::type_info SubmergedCompatibility::SubmarineStatusType;
MethodInfo *SubmergedCompatibility::CalculateLightRadiusMethod;
std::type_info SubmergedCompatibility::TaskIsEmergencyPatchType;
FieldInfo *SubmergedCompatibility::DisableO2MaskCheckField;
MethodInfo *SubmergedCompatibility::RpcRequestChangeFloorMethod;
std::type_info SubmergedCompatibility::FloorHandlerType;
MethodInfo *SubmergedCompatibility::GetFloorHandlerMethod;
FieldInfo *SubmergedCompatibility::OnUpperField;
std::type_info SubmergedCompatibility::Vent_MoveToVent_PatchType;
FieldInfo *SubmergedCompatibility::InTransitionField;
std::type_info SubmergedCompatibility::CustomTaskTypesType;
FieldInfo *SubmergedCompatibility::RetrieveOxigenMaskField;
TaskTypes *SubmergedCompatibility::RetrieveOxygenMask;
std::type_info SubmergedCompatibility::SubmarineOxygenSystemType;
FieldInfo *SubmergedCompatibility::SubmarineOxygenSystemInstanceField;
MethodInfo *SubmergedCompatibility::RepairDamageMethod;

	void SubmergedCompatibility::Initialize()
	{
		PluginInfo *plugin;
		setLoaded(IL2CPPChainloader::Instance->Plugins.TryGetValue(SUBMERGED_GUID, plugin));
		if (!getLoaded())
		{
			return;
		}

	//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
	//ORIGINAL LINE: Plugin = plugin!.Instance as BasePlugin;
		setPlugin(dynamic_cast<BasePlugin*>(plugin->Instance));
		setVersion(plugin->Metadata->Version);

	//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
	//ORIGINAL LINE: Assembly = Plugin!.GetType().Assembly;
		setAssembly(getPlugin()->GetType()->Assembly);
		setTypes(AccessTools::GetTypesFromAssembly(getAssembly()));

		setInjectedTypes(static_cast<std::unordered_map<std::wstring, std::type_info>>(AccessTools::PropertyGetter(getTypes().FirstOrDefault([&] (std::any t)
		{
			return t->Name == L"RegisterInIl2CppAttribute";
		}), L"RegisteredTypes").Invoke(nullptr, Array::Empty<std::any>())));

		SubmarineStatusType = getTypes().First([&] (std::any t)
		{
			return t->Name == L"SubmarineStatus";
		});
		CalculateLightRadiusMethod = AccessTools::Method(SubmarineStatusType, L"CalculateLightRadius");

		TaskIsEmergencyPatchType = getTypes().First([&] (std::any t)
		{
			return t->Name == L"PlayerTask_TaskIsEmergency_Patch";
		});
		DisableO2MaskCheckField = AccessTools::Field(TaskIsEmergencyPatchType, L"DisableO2MaskCheck");

		FloorHandlerType = getTypes().First([&] (std::any t)
		{
			return t->Name == L"FloorHandler";
		});
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
		GetFloorHandlerMethod = AccessTools::Method(FloorHandlerType, L"GetFloorHandler", std::vector<std::type_info> {typeof(PlayerControl)});
		RpcRequestChangeFloorMethod = AccessTools::Method(FloorHandlerType, L"RpcRequestChangeFloor");
		OnUpperField = AccessTools::Field(FloorHandlerType, L"OnUpper");

		Vent_MoveToVent_PatchType = getTypes().First([&] (std::any t)
		{
			return t->Name == L"Vent_MoveToVent_Patch";

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
