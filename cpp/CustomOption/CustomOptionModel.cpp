//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "CustomOptionModel.h"
#include "../Main.h"
#include "../Helpers/CachedPlayer.h"
#include "../Mode/ModeHandler.h"
#include "../TranslateDate.h"
#include "../ModHelpers.h"
#include "CustomOptionDate.h"
#include "../Helpers/FastDestroyableSingleton.h"

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

std::vector<CustomOption*> CustomOption::options;
int CustomOption::preset = 0;

	bool CustomOption::getEnabled() const
	{
		return this->getBool();
	}

	CustomOption::CustomOption()
	{

	}

	CustomOption::CustomOption(int id, bool IsSHROn, CustomOptionType type, const std::wstring &name, std::vector<std::any> &selections, std::any defaultValue, CustomOption *parent, bool isHeader, bool isHidden, const std::wstring &format)
	{
		this->id = id;
		this->isSHROn = IsSHROn;
		this->type = type;
		this->name = name;
		this->format = format;
		this->selections = selections;
		int index = Array::IndexOf(selections, defaultValue);
		this->defaultSelection = index >= 0 ? index : 0;
		this->parent = parent;
		this->isHeader = isHeader;
		this->isHidden = isHidden;

		this->children = std::vector<CustomOption*>();
		if (parent != nullptr)
		{
			parent->children.push_back(this);
		}

		selection = 0;
		if (id > 0)
		{
			entry = SuperNewRolesPlugin::Instance->Config.Bind(StringHelper::formatSimple(L"Preset{0}", preset), std::to_wstring(id), defaultSelection);
			selection = Mathf::Clamp(entry->Value, 0, selections.size() - 1);
			if (options.Any([&] (std::any x)
			{
				return x->id == id;
			}))
			{
				SuperNewRolesPlugin::Logger->LogInfo(L"CustomOptionのId(" + std::to_wstring(id) + L")が重複しています。");
			}
			if (Max < id)
			{
				Max = id;
			}
		}
		options.push_back(this);
	}

int CustomOption::Max = 0;

	CustomOption *CustomOption::Create(int id, bool IsSHROn, CustomOptionType type, const std::wstring &name, std::vector<std::wstring> &selections, CustomOption *parent, bool isHeader, bool isHidden, const std::wstring &format)
	{
		return new CustomOption(id, IsSHROn, type, name, selections, L"", parent, isHeader, isHidden, format);
	}

	CustomOption *CustomOption::Create(int id, bool IsSHROn, CustomOptionType type, const std::wstring &name, float defaultValue, float min, float max, float step, CustomOption *parent, bool isHeader, bool isHidden, const std::wstring &format)
	{
		std::vector<float> selections;
		for (float s = min; s <= max; s += step)
		{
			selections.push_back(s);
		}
		return new CustomOption(id, IsSHROn, type, name, selections.Cast<std::any>()->ToArray(), defaultValue, parent, isHeader, isHidden, format);
	}

	CustomOption *CustomOption::Create(int id, bool IsSHROn, CustomOptionType type, const std::wstring &name, bool defaultValue, CustomOption *parent, bool isHeader, bool isHidden, const std::wstring &format)
	{
		return new CustomOption(id, IsSHROn, type, name, {L"optionOff", L"optionOn"}, defaultValue ? L"optionOn" : L"optionOff", parent, isHeader, isHidden, format);
	}

	void CustomOption::switchPreset(int newPreset)
	{
		CustomOption::preset = newPreset;
		for (auto option : CustomOption::options)
		{
			if (option->id <= 0)
			{
				continue;
			}

			option->entry = SuperNewRolesPlugin::Instance->Config.Bind(StringHelper::formatSimple(L"Preset{0}", preset), std::to_wstring(option->id), option->defaultSelection);
			option->selection = Mathf::Clamp(option->entry->Value, 0, option->selections.size() - 1);
			if (option->optionBehaviour != nullptr and_Keyword StringOption stringOption)
			{
				stringOption->oldValue = stringOption->Value = option->selection;
				stringOption::ValueText->text = option->getString();
			}
		}
	}

	void CustomOption::ShareOptionSelections()
	{
		if (CachedPlayer::AllPlayers.size() <= 1 || (AmongUsClient->Instance == nullptr ? nullptr : AmongUsClient::Instance->AmHost == false && PlayerControl->LocalPlayer == nullptr))
		{
			return;
		}

		MessageWriter *messageWriter = AmongUsClient::Instance->StartRpc(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ShareOptions), Hazel::SendOption::Reliable);
		messageWriter->WritePacked(static_cast<unsigned int>(CustomOption::options.size()));
		for (auto option : CustomOption::options)
		{
			messageWriter->WritePacked(static_cast<unsigned int>(option->id));
			messageWriter->WritePacked(static_cast<unsigned int>(static_cast<unsigned int>(option->selection)));
		}
		messageWriter->EndMessage();
	}

	int CustomOption::getSelection()
	{
		return selection;
	}

	bool CustomOption::getBool()
	{
		return selection > 0;
	}

	float CustomOption::getFloat()
	{
		return std::any_cast<float>(selections[selection]);
	}

	std::wstring CustomOption::getString()
	{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		std::wstring sel = selections[selection].ToString();
		if (format != L"")
		{
			return sel;
		}
		return ModTranslation::getString(sel);
	}

	std::wstring CustomOption::getName()
	{
		return ModTranslation::getString(name);
	}

	void CustomOption::updateSelection(int newSelection)
	{
		selection = Mathf::Clamp((newSelection + selections.size()) % selections.size(), 0, selections.size() - 1);
		if (optionBehaviour != nullptr and_Keyword StringOption stringOption)
		{
			stringOption->oldValue = stringOption->Value = selection;
			stringOption::ValueText->text = getString();

			if (AmongUsClient->Instance == nullptr ? nullptr : AmongUsClient::Instance->AmHost == true && PlayerControl::LocalPlayer)
			{
				if (id == 0)
				{
					switchPreset(selection); // Switch presets
				}
				else if (entry != nullptr)
				{
					entry->Value = selection; // Save selection to config
				}

				ShareOptionSelections(); // Share all selections
			}
		}
	}

std::vector<CustomRoleOption*> CustomRoleOption::RoleOptions;

	int CustomRoleOption::getRate() const
	{
		return getSelection();
	}

	bool CustomRoleOption::isRoleEnable() const
	{
		return getSelection() != 0;
	}

	IntroDate *CustomRoleOption::getIntro() const
	{
		return IntroDate::GetIntroDate(RoleId);
	}


//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
