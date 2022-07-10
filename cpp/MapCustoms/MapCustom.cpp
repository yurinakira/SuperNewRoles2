#include "MapCustom.h"

using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::MapCustoms::Airship;

namespace SuperNewRoles::MapCustoms
{

CustomOption::CustomOption *MapCustom::MapCustomOption;
CustomOption::CustomOption *MapCustom::SkeldSetting;
CustomOption::CustomOption *MapCustom::MiraSetting;
CustomOption::CustomOption *MapCustom::MiraAdditionalVents;
CustomOption::CustomOption *MapCustom::AddVitalsMira;
CustomOption::CustomOption *MapCustom::PolusSetting;
CustomOption::CustomOption *MapCustom::PolusAdditionalVents;
CustomOption::CustomOption *MapCustom::SpecimenVital;
CustomOption::CustomOption *MapCustom::AirshipSetting;
CustomOption::CustomOption *MapCustom::SecretRoomOption;
CustomOption::CustomOption *MapCustom::AirShipAdditionalVents;
CustomOption::CustomOption *MapCustom::AirshipDisableMovingPlatform;
CustomOption::CustomOption *MapCustom::RecordsAdminDestroy;
CustomOption::CustomOption *MapCustom::MoveElecPad;
CustomOption::CustomOption *MapCustom::AddWireTask;

	void MapCustom::CreateOption()
	{
		MapCustomOption = CustomOption::CustomOption::Create(623, false, CustomOptionType::Generic, L"MapCustom", false, nullptr, true);

		/*===============スケルド===============*/
		SkeldSetting = CustomOption::CustomOption::Create(624, false, CustomOptionType::Generic, L"Skeld", false, MapCustomOption);

		/*===============ミラ===============*/
		MiraSetting = CustomOption::CustomOption::Create(660, false, CustomOptionType::Generic, L"Mira", false, MapCustomOption);
		MiraAdditionalVents = CustomOption::CustomOption::Create(631, false, CustomOptionType::Generic, L"MiraAdditionalVents", false, MiraSetting);
		AddVitalsMira = CustomOption::CustomOption::Create(472, false, CustomOptionType::Generic, L"AddVitalsMiraSetting", false, MiraSetting);

		/*===============ポーラス===============*/
		PolusSetting = CustomOption::CustomOption::Create(661, false, CustomOptionType::Generic, L"Polus", false, MapCustomOption);
		PolusAdditionalVents = CustomOption::CustomOption::Create(662, false, CustomOptionType::Generic, L"PolusAdditionalVents", false, PolusSetting);
		SpecimenVital = CustomOption::CustomOption::Create(613, false, CustomOptionType::Generic, L"SpecimenVitalSetting", false, PolusSetting);

		/*===============エアーシップ===============*/
		AirshipSetting = CustomOption::CustomOption::Create(663, false, CustomOptionType::Generic, L"Airship", false, MapCustomOption);
		SecretRoomOption = CustomOption::CustomOption::Create(664, false, CustomOptionType::Generic, L"SecretRoom", false, AirshipSetting);
		AirShipAdditionalVents = CustomOption::CustomOption::Create(605, false, CustomOptionType::Generic, L"AirShipAdditionalVents", false, AirshipSetting);
		AirshipDisableMovingPlatform = CustomOption::CustomOption::Create(665, false, CustomOptionType::Generic, L"AirshipDisableMovingPlatformSetting", false, AirshipSetting);
		RecordsAdminDestroy = CustomOption::CustomOption::Create(612, false, CustomOptionType::Generic, L"RecordsAdminDestroySetting", false, AirshipSetting);
		MoveElecPad = CustomOption::CustomOption::Create(645, false, CustomOptionType::Generic, L"MoveElecPadSetting", false, AirshipSetting);
		AddWireTask = CustomOption::CustomOption::Create(646, false, CustomOptionType::Generic, L"AddWireTaskSetting", false, AirshipSetting);
	}
}
