#include "CustomPlate.h"
#include "DownLoadCustomPlate.h"
#include "../Main.h"
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

bool CustomPlate::isAdded = false;

	void CustomPlate::UnlockedNamePlatesPatch::Postfix(HatManager *__instance)
	{
		if (isAdded || !DownLoadClass::IsEndDownload)
		{
			return;
		}
		isAdded = true;
		SuperNewRolesPlugin::Logger->LogInfo(L"[CustomPlate] プレート読み込み処理開始");
		auto AllPlates = __instance->allNamePlates;

		auto plateDir = new DirectoryInfo(L"SuperNewRoles\\CustomPlatesChache");
		if (!plateDir->Exists)
		{
			plateDir->Create();
		}
		auto Files = plateDir->GetFiles(L"*.png").ToList();
		Files.AddRange(plateDir->GetFiles(L"*.jpg"));
		auto CustomPlates = std::vector<NamePlateData*>();
		for (auto file : Files)
		{
			try
			{
				auto plate = ScriptableObject::CreateInstance<NamePlateData*>();
				auto FileName = file.Name[0..^4];
				auto Data = DownLoadClass::platedetails.FirstOrDefault([&] (std::any data)
				{
					return data::resource->Replace(L".png", L"") == FileName;
				});
				plate->name = Data->name + L"\nby " + Data->author;
				plate->ProductId = L"CustomNamePlates_" + Data->resource->Replace(L".png", L"")->Replace(L".jpg", L"");
				plate->BundleId = L"CustomNamePlates_" + Data->resource->Replace(L".png", L"")->Replace(L".jpg", L"");
				plate->displayOrder = 99;
				plate->ChipOffset = new Vector2(0.0f, 0.2f);
				plate->Free = true;
				plate->viewData->viewData = new NamePlateViewData();
				auto c = plate->viewData.viewData.Image;
				auto d = LoadTex::loadSprite(L"SuperNewRoles\\CustomPlatesChache\\" + Data->resource);
				c = d;
				plate->viewData.viewData->Image = c;
				//CustomPlates.Add(plate);
				//AllPlates.Add(plate);
				__instance->allNamePlates->Add(plate);
				SuperNewRolesPlugin::Logger->LogInfo(L"[CustomPlate] プレート読み込み完了:" + file.Name);
			}
			catch (const std::runtime_error &e)
			{
				SuperNewRolesPlugin::Logger->LogError(L"[CustomPlate:Error] エラー:CustomNamePlateの読み込みに失敗しました:" + file.FullName);
				SuperNewRolesPlugin::Logger->LogError(file.FullName + L"のエラー内容:" + e);
			}
		}
		SuperNewRolesPlugin::Logger->LogInfo(L"[CustomPlate] プレート読み込み処理終了");

		//__instance.allNamePlates = AllPlates;

		delete plateDir;
	}
}
