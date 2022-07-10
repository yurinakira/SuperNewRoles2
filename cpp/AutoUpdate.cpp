#include "AutoUpdate.h"
#include "Main.h"
#include "TranslateDate.h"
#include "Config.h"

using namespace HarmonyLib;
using namespace Newtonsoft::Json::Linq;
using namespace Twitch;
using namespace UnityEngine;

namespace SuperNewRoles
{

	bool AutoUpdate::Announcement::Prefix(AnnouncementPopUp *__instance)
	{
		auto text = __instance->AnnounceTextMeshPro;
		text->text = announcement;
		return false;
	}

	bool AutoUpdate::AnnouncementInitpatch::Prefix(AnnouncementPopUp *__instance)
	{
		__instance->UpdateAnnounceText();
		return false;
	}

std::wstring AutoUpdate::announcement = L"None";
GenericPopup *AutoUpdate::InfoPopup;
bool AutoUpdate::IsLoad = false;
std::wstring AutoUpdate::updateURL = nullptr;

	void AutoUpdate::Load()
	{
	}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<bool> Update()
	Task<bool> *AutoUpdate::Update()
	{
		try
		{
			HttpClient *http = new HttpClient();
			http->DefaultRequestHeaders->Add(L"User-Agent", L"SuperNewRoles Updater");
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
			System::Uri tempVar(updateURL);
			auto response = await http->GetAsync(&tempVar, HttpCompletionOption::ResponseContentRead);
			if (response->StatusCode != HttpStatusCode::OK || response->Content == nullptr)
			{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
				std::wcout << L"Server returned no data: " << response->StatusCode.ToString() << std::endl;

				delete http;
				return false;
			}
			std::wstring codeBase = Assembly::GetExecutingAssembly()->CodeBase;
			System::UriBuilder *uri = new System::UriBuilder(codeBase);
			std::wstring fullname = System::Uri::UnescapeDataString(uri->Path);
			if (FileSystem::fileExists(fullname + L".old")) // Clear old file in case it wasnt;
			{
				File::Delete(fullname + L".old");
			}

			FileSystem::renamePath(fullname, fullname + L".old"); // rename current executable to old

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var responseStream = await response.Content.ReadAsStreamAsync())
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
			{
				auto responseStream = await response->Content->ReadAsStreamAsync();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using var fileStream = File.Create(fullname);
				{
					auto fileStream = File::Create(fullname);
					// probably want to have proper name here
					responseStream.CopyTo(fileStream);
				}
			}
			SuperNewRolesPlugin::IsUpdate = true;

			delete uri;
			delete http;
			return true;
		}
		catch (const std::runtime_error &ex)
		{
			SuperNewRolesPlugin::Instance->Log->LogError(ex.what());
			std::wcout << ex << std::endl;
		}
		return false;
	}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<bool> checkForUpdate(TMPro.TextMeshPro setdate)
	Task<bool> *AutoUpdate::checkForUpdate(TMPro::TextMeshPro *setdate)
	{
		try
		{
			HttpClient *http = new HttpClient();
			http->DefaultRequestHeaders->Add(L"User-Agent", L"SuperNewRoles Updater");
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
			System::Uri tempVar(L"https://api.github.com/repos/ykundesu/SuperNewRoles/releases/latest");
			auto response = await http->GetAsync(&tempVar, HttpCompletionOption::ResponseContentRead);
			if (response->StatusCode != HttpStatusCode::OK || response->Content == nullptr)
			{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
				std::wcout << L"Server returned no data: " << response->StatusCode.ToString() << std::endl;

				delete http;
				return false;
			}
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
			std::wstring json = await response->Content->ReadAsStringAsync();
			JObject *data = JObject::Parse(json);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
			std::wstring tagname = data[L"tag_name"] == nullptr ? L"" : data[L"tag_name"].ToString();
			if (tagname == L"")
			{
				delete http;
				return false; // Something went wrong
			}
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
			std::wstring changeLog = data[L"body"] == nullptr ? L"" : data[L"body"].ToString();
			if (changeLog != L"")
			{
				announcement = changeLog;
			}
			// check version
			SuperNewRolesPlugin::NewVersion = StringHelper::replace(tagname, L"v", L"");
			System::Version *newver = System::Version::Parse(SuperNewRolesPlugin::NewVersion);
			System::Version *Version = SuperNewRolesPlugin::Version;
			announcement = std::wstring::Format(ModTranslation::getString(L"announcementUpdate"), newver, announcement);
			if (!ConfigRoles::getAutoUpdate()->Value)
			{
				delete http;
				return false;
			}
			if (!IsLoad)
			{
				AutoUpdate::Load();
				IsLoad = true;
			}
			if (newver == Version)
			{
				if (ConfigRoles::getDebugMode()->Value)
				{
					SuperNewRolesPlugin::Logger->LogInfo(L"最新バージョンです");
				}
			}
			else
			{
				if (ConfigRoles::getDebugMode()->Value)
				{
					SuperNewRolesPlugin::Logger->LogInfo(L"古いバージョンです");
				}
				JToken *assets = data[L"assets"];
				if (!assets->HasValues)
				{
					delete http;
					return false;
				}
				for (JToken *current = assets->First; current != nullptr; current = current->Next)
				{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
					std::wstring browser_download_url = current[L"browser_download_url"] == nullptr ? L"" : current[L"browser_download_url"].ToString();
					if (browser_download_url != L"" && current[L"content_type"] != nullptr)
					{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
						if (current[L"content_type"].ToString().Equals(L"application/x-msdownload") && StringHelper::endsWith(browser_download_url, L".dll"))
						{
							updateURL = browser_download_url;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
							await Update();
							setdate->SetText(ModTranslation::getString(L"creditsMain") + L"\n" + std::wstring::Format(ModTranslation::getString(L"creditsUpdateOk"), SuperNewRolesPlugin::NewVersion));
							ConfigRoles::isUpdate()->Value = true;
						}
					}
				}
			}

			delete http;
			return false;
		}
		catch (const std::runtime_error &e)
		{
			if (ConfigRoles::getDebugMode()->Value)
			{
				SuperNewRolesPlugin::Logger->LogInfo(L"Error:" + e);
			}
			return false;
		}
	}
}
