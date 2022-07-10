#include "CustomVisor.h"
#include "DownLoadCustomVisor.h"
#include "../Main.h"
#include "DownLoadCustomPlate.h"
#include "../ModHelpers.h"
#include "LoadTex.h"

using namespace BepInEx;
using namespace BepInEx::Configuration;
using namespace BepInEx::IL2CPP;
using namespace HarmonyLib;
using namespace Hazel;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics
{

bool CustomVisor::isAdded = false;

	void CustomVisor::UnlockedVisorPatch::Postfix(HatManager *__instance)
	{
		if (isAdded || !DownLoadClassVisor::IsEndDownload)
		{
			return;
		}
		isAdded = true;
		SuperNewRolesPlugin::Logger->LogInfo(L"[CustomVisor] バイザー読み込み処理開始");
		auto AllPlates = __instance->allNamePlates;

		auto plateDir = new DirectoryInfo(L"SuperNewRoles\\CustomVisorsChache");
		if (!plateDir->Exists)
		{
			plateDir->Create();
		}
		auto Files = plateDir->GetFiles(L"*.png").ToList();
		Files.AddRange(plateDir->GetFiles(L"*.jpg"));
		auto CustomPlates = std::vector<VisorData*>();
		for (auto file : Files)
		{
			try
			{
				auto plate = ScriptableObject::CreateInstance<VisorData*>();
				auto FileName = file.Name[0..^4];
				auto Data = DownLoadClassVisor::Visordetails.FirstOrDefault([&] (std::any data)
				{
					return data::resource->Replace(L".png", L"") == FileName;
				});
				plate->name = Data->name + L"\nby " + Data->author;
				plate->ProductId = L"CustomVisors_" + Data->resource->Replace(L".png", L"")->Replace(L".jpg", L"");
				plate->BundleId = L"CustomVisors_" + Data->resource->Replace(L".png", L"")->Replace(L".jpg", L"");
				plate->displayOrder = 99;
				plate->ChipOffset = new Vector2(0.0f, 0.2f);
				plate->Free = true;
				plate->viewData->viewData = new VisorViewData();
				if (Data->IsTOP)
				{
					plate->viewData.viewData->IdleFrame = ModHelpers::CreateSprite(L"SuperNewRoles\\CustomVisorsChache\\" + file.Name, true);
				}
				else
				{
					plate->viewData.viewData->IdleFrame = LoadTex::loadSprite(L"SuperNewRoles\\CustomVisorsChache\\" + file.Name);
				}
				__instance->allVisors->Add(plate);
				SuperNewRolesPlugin::Logger->LogInfo(L"[CustomVisor] バイザー読み込み完了:" + file.Name);
			}
			catch (const std::runtime_error &e)
			{
				SuperNewRolesPlugin::Logger->LogError(L"[CustomVisor:Error] エラー:CustomVisorの読み込みに失敗しました:" + file.FullName);
				SuperNewRolesPlugin::Logger->LogError(file.FullName + L"のエラー内容:" + e);
			}
		}
		SuperNewRolesPlugin::Logger->LogInfo(L"[CustomVisor] バイザー読み込み処理終了");

		delete plateDir;
	}
}
