#include "DesyncHelpers.h"
#include "../ModHelpers.h"

using namespace Hazel;
using namespace InnerNet;

namespace SuperNewRoles::Helpers
{

	void DesyncHelpers::RPCMurderPlayerPrivate(PlayerControl *source, PlayerControl *target, PlayerControl *see)
	{
		PlayerControl *SeePlayer = see;
		if (see == nullptr)
		{
			SeePlayer = source;
		}
		MessageWriter *MurderWriter = AmongUsClient::Instance->StartRpcImmediately(source->NetId, static_cast<unsigned char>(RpcCalls::MurderPlayer), SendOption::Reliable, SuperNewRoles::ModHelpers::getClientId(SeePlayer));
		MessageExtensions::WriteNetObject(MurderWriter, target);
		AmongUsClient::Instance->FinishRpcImmediately(MurderWriter);
	}

	void DesyncHelpers::RPCMurderPlayerPrivate(PlayerControl *source, CustomRpcSender *sender, PlayerControl *target, PlayerControl *see)
	{
		PlayerControl *SeePlayer = see;
		if (see == nullptr)
		{
			SeePlayer = source;
		}
		sender->StartMessage(SuperNewRoles::ModHelpers::getClientId(SeePlayer))->StartRpc(source->NetId, RpcCalls::MurderPlayer).WriteNetObject(target).EndRpc().EndMessage();
	}
}
