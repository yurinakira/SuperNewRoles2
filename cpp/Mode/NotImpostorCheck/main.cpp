#include "main.h"

namespace SuperNewRoles::Mode::NotImpostorCheck
{

std::vector<int> main::Impostors;

	void main::ClearAndReload()
	{
		if (AmongUsClient::Instance->AmHost)
		{
			Impostors = std::vector<int>();
		}
	}
}
