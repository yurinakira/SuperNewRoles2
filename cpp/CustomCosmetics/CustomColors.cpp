//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "CustomColors.h"
#include "../TranslateDate.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Helpers;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics
{

std::unordered_map<int, std::wstring> CustomColors::ColorStrings;
std::vector<int> CustomColors::lighterColors = {3, 4, 5, 7, 10, 11, 13, 14, 17};
unsigned int CustomColors::pickableColors = static_cast<unsigned int>(Palette->ColorNames->Length);

	void CustomColors::Load()
	{
		std::vector<StringNames*> longlist = Enumerable::ToList<StringNames*>(Palette->ColorNames);
		std::vector<Color32*> colorlist = Enumerable::ToList<Color32*>(Palette->PlayerColors);
		std::vector<Color32*> shadowlist = Enumerable::ToList<Color32*>(Palette->ShadowColors);

		CustomColor tempVar = CustomColor();
		tempVar.longname = L"colorSalmon";
		tempVar.color = new Color32(239, 191, 192, std::numeric_limits<unsigned char>::max());
		tempVar.shadow = new Color32(182, 119, 114, std::numeric_limits<unsigned char>::max());
		tempVar.isLighterColor = true;
		CustomColor tempVar2 = CustomColor();
		tempVar2.longname = L"colorBordeaux";
		tempVar2.color = new Color32(109, 7, 26, std::numeric_limits<unsigned char>::max());
		tempVar2.shadow = new Color32(54, 2, 11, std::numeric_limits<unsigned char>::max());
		tempVar2.isLighterColor = false;
		CustomColor tempVar3 = CustomColor();
		tempVar3.longname = L"colorOlive";
		tempVar3.color = new Color32(154, 140, 61, std::numeric_limits<unsigned char>::max());
		tempVar3.shadow = new Color32(104, 95, 40, std::numeric_limits<unsigned char>::max());
		tempVar3.isLighterColor = false;
		CustomColor tempVar4 = CustomColor();
		tempVar4.longname = L"colorTurqoise";
		tempVar4.color = new Color32(22, 132, 176, std::numeric_limits<unsigned char>::max());
		tempVar4.shadow = new Color32(15, 89, 117, std::numeric_limits<unsigned char>::max());
		tempVar4.isLighterColor = false;
		CustomColor tempVar5 = CustomColor();
		tempVar5.longname = L"colorMint";
		tempVar5.color = new Color32(111, 192, 156, std::numeric_limits<unsigned char>::max());
		tempVar5.shadow = new Color32(65, 148, 111, std::numeric_limits<unsigned char>::max());
		tempVar5.isLighterColor = true;
		CustomColor tempVar6 = CustomColor();
		tempVar6.longname = L"colorLavender";
		tempVar6.color = new Color32(173, 126, 201, std::numeric_limits<unsigned char>::max());
		tempVar6.shadow = new Color32(131, 58, 203, std::numeric_limits<unsigned char>::max());
		tempVar6.isLighterColor = true;
		CustomColor tempVar7 = CustomColor();
		tempVar7.longname = L"colorNougat";
		tempVar7.color = new Color32(160, 101, 56, std::numeric_limits<unsigned char>::max());
		tempVar7.shadow = new Color32(115, 15, 78, std::numeric_limits<unsigned char>::max());
		tempVar7.isLighterColor = false;
		CustomColor tempVar8 = CustomColor();
		tempVar8.longname = L"colorPeach";
		tempVar8.color = new Color32(255, 164, 119, std::numeric_limits<unsigned char>::max());
		tempVar8.shadow = new Color32(238, 128, 100, std::numeric_limits<unsigned char>::max());
		tempVar8.isLighterColor = true;
		CustomColor tempVar9 = CustomColor();
		tempVar9.longname = L"colorWasabi";
		tempVar9.color = new Color32(112, 143, 46, std::numeric_limits<unsigned char>::max());
		tempVar9.shadow = new Color32(72, 92, 29, std::numeric_limits<unsigned char>::max());
		tempVar9.isLighterColor = false;
		CustomColor tempVar10 = CustomColor();
		tempVar10.longname = L"colorHotPink";
		tempVar10.color = new Color32(255, 51, 102, std::numeric_limits<unsigned char>::max());
		tempVar10.shadow = new Color32(232, 0, 58, std::numeric_limits<unsigned char>::max());
		tempVar10.isLighterColor = true;
		CustomColor tempVar11 = CustomColor();
		tempVar11.longname = L"colorPetrol";
		tempVar11.color = new Color32(0, 99, 105, std::numeric_limits<unsigned char>::max());
		tempVar11.shadow = new Color32(0, 61, 54, std::numeric_limits<unsigned char>::max());
		tempVar11.isLighterColor = false;
		CustomColor tempVar12 = CustomColor();
		tempVar12.longname = L"colorLemon";
		tempVar12.color = new Color32(0xDB, 0xFD, 0x2F, std::numeric_limits<unsigned char>::max());
		tempVar12.shadow = new Color32(0x74, 0xE5, 0x10, std::numeric_limits<unsigned char>::max());
		tempVar12.isLighterColor = true;
		CustomColor tempVar13 = CustomColor();
		tempVar13.longname = L"colorSignalOrange";
		tempVar13.color = new Color32(0xF7, 0x44, 0x17, std::numeric_limits<unsigned char>::max());
		tempVar13.shadow = new Color32(0x9B, 0x2E, 0x0F, std::numeric_limits<unsigned char>::max());
		tempVar13.isLighterColor = true;
		CustomColor tempVar14 = CustomColor();
		tempVar14.longname = L"colorTeal";
		tempVar14.color = new Color32(0x25, 0xB8, 0xBF, std::numeric_limits<unsigned char>::max());
		tempVar14.shadow = new Color32(0x12, 0x89, 0x86, std::numeric_limits<unsigned char>::max());
		tempVar14.isLighterColor = false;
		CustomColor tempVar15 = CustomColor();
		tempVar15.longname = L"colorBlurple";
		tempVar15.color = new Color32(0x59, 0x3C, 0xD6, std::numeric_limits<unsigned char>::max());
		tempVar15.shadow = new Color32(0x29, 0x17, 0x96, std::numeric_limits<unsigned char>::max());
		tempVar15.isLighterColor = false;
		CustomColor tempVar16 = CustomColor();
		tempVar16.longname = L"colorSunrise";
		tempVar16.color = new Color32(0xFF, 0xCA, 0x19, std::numeric_limits<unsigned char>::max());
		tempVar16.shadow = new Color32(0xDB, 0x44, 0x42, std::numeric_limits<unsigned char>::max());
		tempVar16.isLighterColor = true;
		CustomColor tempVar17 = CustomColor();
		tempVar17.longname = L"colorIce";
		tempVar17.color = new Color32(0xA8, 0xDF, 0xFF, std::numeric_limits<unsigned char>::max());
		tempVar17.shadow = new Color32(0x59, 0x9F, 0xC8, std::numeric_limits<unsigned char>::max());
		tempVar17.isLighterColor = true;
		CustomColor tempVar18 = CustomColor();
		tempVar18.longname = L"colorPitchBlack";
		tempVar18.color = new Color32(0, 0, 0, std::numeric_limits<unsigned char>::max());

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
