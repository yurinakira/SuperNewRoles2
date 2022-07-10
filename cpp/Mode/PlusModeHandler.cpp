#include "PlusModeHandler.h"
#include "PlusMode/Options.h"

using namespace SuperNewRoles::Mode::PlusMode;

namespace SuperNewRoles::Mode
{

std::vector<PlusModeId> PlusModeHandler::thisPlusModes;

	void PlusModeHandler::ClearAndReload()
	{
		thisPlusModes = std::vector<PlusModeId>();
		for (auto mode : PlusModeIds)
		{
			if (isMode(mode))
			{
				thisPlusModes.push_back(mode);
			}
		}
	}

std::vector<PlusModeId> PlusModeHandler::PlusModeIds = {PlusModeId::NotSabotage, PlusModeId::NotTaskWin};

	bool PlusModeHandler::isMode(PlusModeId Modeid)
	{
		bool tempVar6;
		switch (Modeid)
		{
			case PlusModeId::NotSabotage:
				tempVar6 = Options::PlusModeSetting->getBool() && Options::NoSabotageModeSetting->getBool();
				break;
			case PlusModeId::NotTaskWin:
				tempVar6 = Options::PlusModeSetting->getBool() && Options::NoTaskWinModeSetting->getBool();
				break;
			default:
				tempVar6 = false;
				break;
		}
		return tempVar6;
	}
}
