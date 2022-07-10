#pragma once

#include "../CustomRPC/CustomRPCSender.h"

using namespace Hazel;
using namespace InnerNet;

namespace SuperNewRoles::Helpers
{
	class DesyncHelpers final
	{
	public:
		static void RPCMurderPlayerPrivate(PlayerControl *source, PlayerControl *target, PlayerControl *see = nullptr);
		static void RPCMurderPlayerPrivate(PlayerControl *source, CustomRpcSender *sender, PlayerControl *target, PlayerControl *see = nullptr);
	};
}
