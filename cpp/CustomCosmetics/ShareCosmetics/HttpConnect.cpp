#include "HttpConnect.h"
#include "../../Main.h"
#include "SharePatch.h"
#include "SuperNewRoles.CustomCosmetics.ShareCosmetics.CosmeticsObject.h"

using namespace SuperNewRoles::CustomCosmetics::ShareCosmetics;

namespace SuperNewRoles::CustomCosmetics::ShareCosmetics
{

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<string> Download(string url)
	Task<std::wstring> *HttpConnect::Download(const std::wstring &url)
	{
		HttpClient *http = new HttpClient();
		http->DefaultRequestHeaders->Add(L"User-Agent", L"SuperNewRoles CustomCosmetics");
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
		System::Uri tempVar(url);
		auto response = await http->GetAsync(&tempVar, HttpCompletionOption::ResponseContentRead);
		if (response->StatusCode != HttpStatusCode::OK || response->Content == nullptr)
		{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
			std::wcout << L"Server returned no data: " << response->StatusCode.ToString() << std::endl;

			delete http;
			return L"";
		}

		delete http;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
		return await response->Content->ReadAsStringAsync();
	}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<bool> ShareCosmeticDateDownload(byte id, string url)
	Task<bool> *HttpConnect::ShareCosmeticDateDownload(unsigned char id, const std::wstring &url)
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
		auto dldata = await Download(url);

		SuperNewRolesPlugin::Logger->LogInfo(L"DLDATA:" + dldata);
		SharePatch::PlayerDatas[id] = dldata;
		SuperNewRolesPlugin::Logger->LogInfo(L"c");
		auto ms = new MemoryStream(Encoding::UTF8->GetBytes(dldata));
		SuperNewRolesPlugin::Logger->LogInfo(L"e");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
		auto serializer = new DataContractJsonSerializer(typeof(CosmeticsObject));
		SuperNewRolesPlugin::Logger->LogInfo(L"f");
		auto data = serializer->ReadObject(ms);
		SuperNewRolesPlugin::Logger->LogInfo(L"g");
		SharePatch::PlayerObjects[id] = static_cast<CosmeticsObject*>(data);
		SuperNewRolesPlugin::Logger->LogInfo(L"h");

		delete serializer;
//C# TO C++ CONVERTER TODO TASK: A 'delete ms' statement was not added since ms was passed to a method or constructor. Handle memory management manually.
		return false;
	}
}
