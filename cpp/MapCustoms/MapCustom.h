#pragma once

#include "../CustomOption/CustomOptionModel.h"
#include "2_Polus/SpecimenVital.h"
#include "4_Airship/RecordsAdminDestroy.h"
#include "4_Airship/MoveElecPad.h"

using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::MapCustoms::Airship;

namespace SuperNewRoles::MapCustoms
{
	class MapCustom
	{
	public:
		static CustomOption::CustomOption *MapCustomOption;

		static CustomOption::CustomOption *SkeldSetting; //スケルド


		static CustomOption::CustomOption *MiraSetting; //ミラ
		static CustomOption::CustomOption *MiraAdditionalVents;
		static CustomOption::CustomOption *AddVitalsMira;


		static CustomOption::CustomOption *PolusSetting; //ポーラス
		static CustomOption::CustomOption *PolusAdditionalVents;
		static CustomOption::CustomOption *SpecimenVital;


		static CustomOption::CustomOption *AirshipSetting; //エアーシップ
		static CustomOption::CustomOption *SecretRoomOption;
		static CustomOption::CustomOption *AirShipAdditionalVents;
		static CustomOption::CustomOption *AirshipDisableMovingPlatform;
		static CustomOption::CustomOption *RecordsAdminDestroy;
		static CustomOption::CustomOption *MoveElecPad;
		static CustomOption::CustomOption *AddWireTask;


		static void CreateOption();
	};
}
