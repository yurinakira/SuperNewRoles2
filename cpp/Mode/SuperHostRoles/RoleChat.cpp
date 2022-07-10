#include "RoleChat.h"
#include "../../TranslateDate.h"
#include "../../Roles/TeamRoleType.h"

using namespace InnerNet;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::SuperHostRoles
{

	bool RoleChat::SendChat(ChatController *__instance)
	{
		std::wstring text = __instance->TextArea.text;
		std::vector<std::wstring> args = StringHelper::split(text, L' ');
		bool handled = false;
		if (AmongUsClient::Instance->GameState != InnerNetClient::GameStates::Started)
		{
			if (AmongUsClient::Instance->AmHost)
			{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string and was converted to C++ 'if-else' logic:
//				switch (args[0])
//ORIGINAL LINE: case "/help":
				if (args[0] == L"/help")
				{
						if (args.size() != 1)
						{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string and was converted to C++ 'if-else' logic:
//							switch (args[1])
//ORIGINAL LINE: case "role":
							if (args[1] == L"role")
							{
									if (args.size() != 2)
									{
										PlayerControl::LocalPlayer::RpcSendChat(GetRoleDes(args[3]));
									}
							}
						}
						handled = true;
				}
			}
		}
		return handled;
	}

	std::wstring RoleChat::GetRoleDes(const std::wstring &rolename)
	{
		std::wstring IntroDesc;
		std::wstring Desc;
		IntroDate *data = IntroDate::CrewmateIntro;
		if (rolename == ModTranslation::getString(L"LoversName"))
		{
		}
		else
		{
			data = GetNameIntroDate(rolename);
			IntroDesc = data->TitleDesc;
			Desc = data->Description;
		}
		if (data == IntroDate::CrewmateIntro)
		{
			return L"";
		}

		std::wstring team = L"重複";
		if (data->Team == TeamRoleType::Crewmate)
		{
			team = ModTranslation::getString(L"CrewMateName");
		}
		else if (data->Team == TeamRoleType::Impostor)
		{
			team = ModTranslation::getString(L"ImpostorName");
		}
		else if (data->Team == TeamRoleType::Neutral)
		{
			team = ModTranslation::getString(L"NeutralName");
		}
		std::wstring returndata = L"";
		returndata = rolename + L"\n";
		returndata += team + L"陣営\n";
		returndata += data->Description;
		return L"";
	}

	IntroDate *RoleChat::GetNameIntroDate(const std::wstring &role)
	{
		std::unordered_map<std::wstring, IntroDate*> NameData =
		{
			{ModTranslation::getString(L"JesterName"), IntroDate::JesterIntro},
			{ModTranslation::getString(L"SheriffName"), IntroDate::SheriffIntro},
			{ModTranslation::getString(L"MadMateName"), IntroDate::MadMateIntro},
			{ModTranslation::getString(L"BaitName"), IntroDate::BaitIntro},
			{ModTranslation::getString(L"HomeSecurityGuardName"), IntroDate::HomeSecurityGuardIntro},
			{ModTranslation::getString(L"StuntmanName"), IntroDate::StuntManIntro},
			{ModTranslation::getString(L"HomeSecurityGuardName"), IntroDate::HomeSecurityGuardIntro},
			{ModTranslation::getString(L"StuntmanName"), IntroDate::StuntManIntro},
			{ModTranslation::getString(L"EvilGamblerdName"), IntroDate::EvilGamblerIntro},
			{ModTranslation::getString(L"GodName"), IntroDate::GodIntro},
			{ModTranslation::getString(L"MinimalistName"), IntroDate::MinimalistIntro},
			{ModTranslation::getString(L"EgoistName"), IntroDate::EgoistIntro},
			{ModTranslation::getString(L"MayorName"), IntroDate::MayorIntro},
			{ModTranslation::getString(L"trueloverName"), IntroDate::trueloverIntro},
			{ModTranslation::getString(L"TechnicianName"), IntroDate::TechnicianIntro},
			{ModTranslation::getString(L"MadStuntmanName"), IntroDate::MadStuntManIntro},
			{ModTranslation::getString(L"SamuraiName"), IntroDate::SamuraiIntro},
			{ModTranslation::getString(L"BlackCatName"), IntroDate::BlackCatIntro}
		};
		for (auto data : NameData)
		{
			if (data->Key == role)
			{
				return data->Value;
			}
		}
		return IntroDate::CrewmateIntro;
	}
}
