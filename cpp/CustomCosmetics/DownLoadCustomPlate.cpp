//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "DownLoadCustomPlate.h"
#include "../Patch/LogoAndStamp.h"
#include "../Main.h"

using namespace HarmonyLib;
using namespace Newtonsoft::Json::Linq;
using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics
{

	std::wstring CustomPlates::CustomPlate::getAuthor() const
	{
		return author;
	}

	void CustomPlates::CustomPlate::setAuthor(const std::wstring &value)
	{
		author = value;
	}

	std::wstring CustomPlates::CustomPlate::getName() const
	{
		return name;
	}

	void CustomPlates::CustomPlate::setName(const std::wstring &value)
	{
		name = value;
	}

	std::wstring CustomPlates::CustomPlate::getResource() const
	{
		return resource;
	}

	void CustomPlates::CustomPlate::setResource(const std::wstring &value)
	{
		resource = value;
	}

	std::wstring CustomPlates::CustomPlate::getReshasha() const
	{
		return reshasha;
	}

	void CustomPlates::CustomPlate::setReshasha(const std::wstring &value)
	{
		reshasha = value;
	}

bool DownLoadClass::IsEndDownload = false;
bool DownLoadClass::running = false;
std::vector<std::wstring> DownLoadClass::fetchs;
std::vector<CustomPlates::CustomPlate*> DownLoadClass::platedetails;

	void DownLoadClass::Load()
	{
		Patches::CredentialsPatch::LogoPatch::FetchBoosters();
		if (running)
		{
			return;
		}
		IsEndDownload = false;
		FileSystem::createDirectory(FileSystem::getDirectoryName(Application->dataPath) + LR"(\SuperNewRoles\)");
		FileSystem::createDirectory(FileSystem::getDirectoryName(Application->dataPath) + LR"(\SuperNewRoles\CustomPlatesChache\)");
		SuperNewRolesPlugin::Logger->LogInfo(L"[CustomPlate:Download] ダウンロード開始");
		FetchHats(L"https://raw.githubusercontent.com/ykundesu/SuperNewNamePlates/main");
		running = true;
	}

	std::wstring DownLoadClass::sanitizeResourcePath(const std::wstring &res)
	{
		if (res == L"" || !StringHelper::endsWith(res, L".png"))
		{
			return L"";
		}

		res = StringHelper::replace(StringHelper::replace(StringHelper::replace(StringHelper::replace(res, L"\\", L""), L"/", L""), L"*", L""), L"..", L"");
		return res;
	}

	bool DownLoadClass::doesResourceRequireDownload(const std::wstring &respath, const std::wstring &reshash, MD5 *md5)
	{
		if (reshash == L"" || !FileSystem::fileExists(respath))
		{
			return true;
		}

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using var stream = File.OpenRead(respath);
		{
			auto stream = File::OpenRead(respath);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct C++ equivalent to this .NET String method:
			auto hash = System::BitConverter::ToString(md5->ComputeHash(stream)).Replace(L"-", L"").ToLowerInvariant();
			return reshash != hash;
		}
	}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<HttpStatusCode> FetchHats(string repo)
	Task<HttpStatusCode> *DownLoadClass::FetchHats(const std::wstring &repo)
	{
		fetchs.push_back(repo);
		SuperNewRolesPlugin::Logger->LogInfo(L"[CustomPlate:Download] ダウンロード開始:" + repo);
		HttpClient *http = new HttpClient();
		http->DefaultRequestHeaders->CacheControl = new CacheControlHeaderValue();
		http->DefaultRequestHeaders.CacheControl->NoCache = true;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
		System::Uri tempVar(StringHelper::formatSimple(L"{0}/CustomNamePlates.json", repo));
		auto response = await http->GetAsync(&tempVar, HttpCompletionOption::ResponseContentRead);
		try
		{
			if (response->StatusCode != HttpStatusCode::OK)
			{
				delete http;
				return response->StatusCode;
			}
			if (response->Content == nullptr)
			{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
				std::wcout << L"Server returned no data: " << response->StatusCode.ToString() << std::endl;

				delete http;
				return HttpStatusCode::ExpectationFailed;
			}
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
			std::wstring json = await response->Content->ReadAsStringAsync();
			JToken *jobj = JObject::Parse(json)[L"nameplates"];
			if (!jobj->HasValues)
			{
				delete http;
				return HttpStatusCode::ExpectationFailed;
			}

			std::vector<CustomPlates::CustomPlate*> platedatas;

			for (JToken *current = jobj->First; current != nullptr; current = current->Next)
			{
				if (current->HasValues)
				{
					class AnonymousType
					{
					public:
						std::wstring name;
						std::wstring resource;

						AnonymousType(std::wstring name, std::wstring resource) : name(name), resource(resource) {}
					};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
					CustomPlates::CustomPlate *info = AnonymousType(current[L"name"] == nullptr ? nullptr : current[L"name"].ToString(), sanitizeResourcePath(current[L"resource"] == nullptr ? L"" : current[L"resource"].ToString()));
					if (info.resource == L"" || info.name == L"") // required
					{
						continue;
					}
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
					info.setAuthor(current[L"author"] == nullptr ? L"" : current[L"author"].ToString());
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
					info.setReshasha(current[L"name"] == nullptr ? L"" : current[L"name"].ToString());
					platedatas.push_back(info);
				}
			}

			std::vector<std::wstring> markedfordownload;

			std::wstring filePath = FileSystem::getDirectoryName(Application->dataPath) + LR"(\SuperNewRoles\CustomPlatesChache\)";
			MD5 *md5 = MD5::Create();
			for (auto data : platedatas)
			{
				if (doesResourceRequireDownload(filePath + data->getResource(), data->getReshasha(), md5))
				{
					markedfordownload.push_back(data->getResource());
				}
			}

			for (auto file : markedfordownload)
			{

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
				auto hatFileResponse = await http->GetAsync(StringHelper::formatSimple(L"{0}/NamePlates/{1}", repo, file), HttpCompletionOption::ResponseContentRead);
				if (hatFileResponse->StatusCode != HttpStatusCode::OK)
				{
					continue;
				}
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using var responseStream = await hatFileResponse.Content.ReadAsStreamAsync();
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
				{
					auto responseStream = await hatFileResponse->Content->ReadAsStreamAsync();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using var fileStream = File.Create(string.Format("{0}\\{1}", filePath, file));
					{
						auto fileStream = File::Create(StringHelper::formatSimple(L"{0}\\{1}", filePath, file));
						responseStream.CopyTo(fileStream);
					}
				}
			}

			platedetails.insert(platedetails.end(), platedatas.begin(), platedatas.end());
		}
		catch (const std::runtime_error &ex)
		{
			SuperNewRolesPlugin::Instance->Log->LogError(ex.what());
			std::wcout << ex << std::endl;
		}
		SuperNewRolesPlugin::Logger->LogInfo(L"[CustomPlate:Download] ダウンロード終了:" + repo);
		fetchs.Remove(repo);

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
