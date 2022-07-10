#pragma once

#include <vector>

using namespace SuperNewRoles::Mode::PlusMode;

namespace SuperNewRoles::Mode
{
	enum class PlusModeId
	{
		No,
		NotSabotage,
		NotTaskWin
	};
	class PlusModeHandler
	{
	public:
		static std::vector<PlusModeId> thisPlusModes;
		static void ClearAndReload();
		static std::vector<PlusModeId> PlusModeIds;
		static bool isMode(PlusModeId Modeid);
	};
}
