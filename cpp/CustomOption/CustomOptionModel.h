#pragma once

//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "../CustomRPC/CustomRPC.h"
#include "../Intro/IntroDate.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <any>
#include <functional>
#include "../stringhelper.h"
#include "../stringbuilder.h"

using namespace BepInEx::Configuration;
using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;
using namespace UnityEngine::Events;

namespace SuperNewRoles::CustomOption
{
	enum class CustomOptionType
	{
		Generic,
		Impostor,
		Neutral,
		Crewmate

	};

	class CustomOption
	{
	public:
		static std::vector<CustomOption*> options;
		static int preset;

		int id = 0;
		bool isSHROn = false;
		CustomOptionType type = static_cast<CustomOptionType>(0);
		std::wstring name;
		std::wstring format;
		std::vector<std::any> selections;

		int defaultSelection = 0;
		ConfigEntry<int> *entry;
		int selection = 0;
		OptionBehaviour *optionBehaviour;
		CustomOption *parent;
		std::vector<CustomOption*> children;
		bool isHeader = false;
		bool isHidden = false;

		virtual ~CustomOption()
		{
			delete entry;
			delete optionBehaviour;
			delete parent;
		}

		virtual bool getEnabled() const;

		// Option creation
		CustomOption();

		CustomOption(int id, bool IsSHROn, CustomOptionType type, const std::wstring &name, std::vector<std::any> &selections, std::any defaultValue, CustomOption *parent, bool isHeader, bool isHidden, const std::wstring &format);
		static int Max;

		static CustomOption *Create(int id, bool IsSHROn, CustomOptionType type, const std::wstring &name, std::vector<std::wstring> &selections, CustomOption *parent = nullptr, bool isHeader = false, bool isHidden = false, const std::wstring &format = L"");

		static CustomOption *Create(int id, bool IsSHROn, CustomOptionType type, const std::wstring &name, float defaultValue, float min, float max, float step, CustomOption *parent = nullptr, bool isHeader = false, bool isHidden = false, const std::wstring &format = L"");

		static CustomOption *Create(int id, bool IsSHROn, CustomOptionType type, const std::wstring &name, bool defaultValue, CustomOption *parent = nullptr, bool isHeader = false, bool isHidden = false, const std::wstring &format = L"");

		// Static behaviour

		static void switchPreset(int newPreset);

		static void ShareOptionSelections();

		// Getter

		virtual int getSelection();

		virtual bool getBool();

		virtual float getFloat();

		virtual std::wstring getString();

		virtual std::wstring getName();

		// Option changes

		virtual void updateSelection(int newSelection);
	};
	class CustomRoleOption : public CustomOption
	{
	public:
		static std::vector<CustomRoleOption*> RoleOptions;

		CustomOption *countOption = nullptr;

		RoleId RoleId = static_cast<RoleId>(0);

		virtual ~CustomRoleOption()
		{
			delete countOption;
		}

		int getRate() const;

		bool isRoleEnable() const;

		IntroDate *getIntro() const;

		int getCount() const;

//C# TO C++ CONVERTER TODO TASK: Methods returning tuples are not converted by C# to C++ Converter:
//		public (int, int) data
//		{
//			get
//			{
//				return (rate, count);
//			}
//		}

		CustomRoleOption(int id, bool isSHROn, CustomOptionType type, const std::wstring &name, Color *color, int max = 15);
	};
	class CustomOptionBlank : public CustomOption
	{
	public:
		CustomOptionBlank(CustomOption *parent);

		int getSelection() override;

		bool getBool() override;

		float getFloat() override;

		std::wstring getString() override;

		void updateSelection(int newSelection) override;

	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(RoleOptionsData), nameof(RoleOptionsData.GetNumPerGame))] class RoleOptionsDataGetNumPerGamePatch
	class RoleOptionsDataGetNumPerGamePatch
	{
	public:
		static void Postfix(int &__result, RoleTypes *&role);
	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameOptionsMenu), nameof(GameOptionsMenu.Start))] class GameOptionsMenuStartPatch
	class GameOptionsMenuStartPatch
	{
	public:
		static void Postfix(GameOptionsMenu *__instance);
	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(KeyValueOption), nameof(KeyValueOption.OnEnable))] public class KeyValueOptionEnablePatch
	class KeyValueOptionEnablePatch
	{
	public:
		static void Postfix(KeyValueOption *__instance);
	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(StringOption), nameof(StringOption.OnEnable))] public class StringOptionEnablePatch
	class StringOptionEnablePatch
	{
	public:
		static bool Prefix(StringOption *__instance);
	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(StringOption), nameof(StringOption.Increase))] public class StringOptionIncreasePatch
	class StringOptionIncreasePatch
	{
	public:
		static bool Prefix(StringOption *__instance);
	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(StringOption), nameof(StringOption.Decrease))] public class StringOptionDecreasePatch

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
