//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "DownLoadCustomVisor.h"
#include "../Main.h"

using namespace HarmonyLib;
using namespace Newtonsoft::Json::Linq;
using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics
{

	std::wstring CustomVisors::CustomVisor::getAuthor() const
	{
		return author;
	}

	void CustomVisors::CustomVisor::setAuthor(const std::wstring &value)
	{
		author = value;
	}

	std::wstring CustomVisors::CustomVisor::getName() const
	{
		return name;
	}

	void CustomVisors::CustomVisor::setName(const std::wstring &value)
	{
		name = value;
	}

	std::wstring CustomVisors::CustomVisor::getResource() const
	{
		return resource;
	}

	void CustomVisors::CustomVisor::setResource(const std::wstring &value)
	{
		resource = value;
	}

	std::wstring CustomVisors::CustomVisor::getReshasha() const
	{
		return reshasha;
	}

	void CustomVisors::CustomVisor::setReshasha(const std::wstring &value)
	{
		reshasha = value;
	}

	bool CustomVisors::CustomVisor::isTOP() const
	{
		return IsTOP;
	}

	void CustomVisors::CustomVisor::setTOP(bool value)
	{
		IsTOP = value;
	}

bool DownLoadClassVisor::IsEndDownload = false;
bool DownLoadClassVisor::running = false;
std::vector<std::wstring> DownLoadClassVisor::fetchs;
std::vector<CustomVisors::CustomVisor*> DownLoadClassVisor::Visordetails;

	void DownLoadClassVisor::Load()
	{
		if (running)
		{
			return;
		}
		IsEndDownload = false;
		FileSystem::createDirectory(FileSystem::getDirectoryName(Application->dataPath) + LR"(\SuperNewRoles\)");
		FileSystem::createDirectory(FileSystem::getDirectoryName(Application->dataPath) + LR"(\SuperNewRoles\CustomVisorsChache\)");
		SuperNewRolesPlugin::Logger->LogInfo(L"[CustomVisor:Download] バイザーダウンロード開始");
		FetchHats(L"https://raw.githubusercontent.com/ykundesu/SuperNewNamePlates/main");
		FetchHats(L"https://raw.githubusercontent.com/hinakkyu/TheOtherHats/master");
		FetchHats(L"https://raw.githubusercontent.com/Ujet222/TOPVisors/main", true);
		running = true;
	}

	std::wstring DownLoadClassVisor::sanitizeResourcePath(const std::wstring &res)
	{
		if (res == L"" || !StringHelper::endsWith(res, L".png"))
		{
			return L"";
		}

		res = StringHelper::replace(StringHelper::replace(StringHelper::replace(StringHelper::replace(res, L"\\", L""), L"/", L""), L"*", L""), L"..", L"");
		return res;
	}

	bool DownLoadClassVisor::doesResourceRequireDownload(const std::wstring &respath, const std::wstring &reshash, MD5 *md5)
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
//ORIGINAL LINE: public static async Task<HttpStatusCode> FetchHats(string repo, bool IsTOP = false)
	Task<HttpStatusCode> *DownLoadClassVisor::FetchHats(const std::wstring &repo, bool IsTOP)
	{
		fetchs.push_back(repo);
		SuperNewRolesPlugin::Logger->LogInfo(L"[CustomVisor:Download] バイザーダウンロード開始:" + repo);
		HttpClient *http = new HttpClient();
		http->DefaultRequestHeaders->CacheControl = new CacheControlHeaderValue();
		http->DefaultRequestHeaders.CacheControl->NoCache = true;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
		System::Uri tempVar(StringHelper::formatSimple(L"{0}/CustomVisors.json", repo));
		auto response = await http->GetAsync(&tempVar, HttpCompletionOption::ResponseContentRead);
		try
		{
			if (response->StatusCode != HttpStatusCode::OK)
			{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
				System::Uri tempVar2(StringHelper::formatSimple(L"{0}/CustomHats.json", repo));
				response = await http->GetAsync(&tempVar2, HttpCompletionOption::ResponseContentRead);
				if (response->StatusCode != HttpStatusCode::OK)
				{
					delete http;
					return response->StatusCode;
				}
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
			std::wstring visortext = L"Visors";
			JToken *jobj = JObject::Parse(json)[L"Visors"];
			if (jobj == nullptr || !jobj->HasValues)
			{
				visortext = L"visors";
				jobj = JObject::Parse(json)[L"visors"];
				if (jobj == nullptr || !jobj->HasValues)
				{
					delete http;
					return HttpStatusCode::ExpectationFailed;
				}
			};

			std::vector<CustomVisors::CustomVisor*> Visordatas;

			for (JToken *current = jobj->First; current != nullptr; current = current->Next)
			{
				if (current != nullptr && current->HasValues)
				{
					class AnonymousType
					{
					public:
						std::wstring name;
						std::wstring resource;

						AnonymousType(std::wstring name, std::wstring resource) : name(name), resource(resource) {}
					};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
					CustomVisors::CustomVisor *info = AnonymousType(current[L"name"] == nullptr ? nullptr : current[L"name"].ToString(), sanitizeResourcePath(current[L"resource"] == nullptr ? L"" : current[L"resource"].ToString()));
					if (info.resource == L"" || info.name == L"") // required
					{
						continue;
					}
					info.setTOP(IsTOP);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
					info.setAuthor(current[L"author"] == nullptr ? L"" : current[L"author"].ToString());
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
					info.setReshasha(current[L"name"] == nullptr ? L"" : current[L"name"].ToString());
					Visordatas.push_back(info);
				}
			}

			std::vector<std::wstring> markedfordownload;

			std::wstring filePath = FileSystem::getDirectoryName(Application->dataPath) + LR"(\SuperNewRoles\CustomVisorsChache\)";
			MD5 *md5 = MD5::Create();
			for (auto data : Visordatas)
			{
				if (doesResourceRequireDownload(filePath + data->getResource(), data->getReshasha(), md5))
				{

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
