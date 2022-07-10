#pragma once

#include <string>
#include <functional>
#include "exceptionhelper.h"
#include "../stringhelper.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace UnhollowerBaseLib;
//TOHの開発者さんたち(主に空き瓶さん)ありがとうございます

namespace SuperNewRoles
{

	class CustomRpcSender
	{
	public:
		MessageWriter *stream;
		const std::wstring name;
		SendOption *const sendOption;
		bool isUnsafe = false;
		using onSendDelegateType = std::function<void ()>;
		onSendDelegateType onSendDelegate;

	private:
		State currentState = State::Ready;

		//0~: targetClientId (GameDataTo)
		//-1: 全プレイヤー (GameData)
		//-2: 未設定
		int currentRpcTarget = 0;

	public:
		virtual ~CustomRpcSender()
		{
			delete stream;
			delete sendOption;
		}

	private:
		CustomRpcSender();
	public:
		CustomRpcSender(const std::wstring &name, SendOption *sendOption, bool isUnsafe);
		static CustomRpcSender *Create(const std::wstring &name = L"No Name Sender", SendOption *sendOption = SendOption::None, bool isUnsafe = false);

//		#region Start/End Message
		CustomRpcSender *StartMessage(int targetClientId = -1);
		CustomRpcSender *EndMessage(int targetClientId = -1);
//		#endregion
//		#region Start/End Rpc
		CustomRpcSender *StartRpc(unsigned int targetNetId, RpcCalls *rpcCall);
		CustomRpcSender *StartRpc(unsigned int targetNetId, unsigned char callId);
		CustomRpcSender *EndRpc();
//		#endregion
		CustomRpcSender *AutoStartRpc(unsigned int targetNetId, unsigned char callId, int targetClientId = -1);
		void SendMessage();

		// Write
//		#region PublicWriteMethods
		CustomRpcSender *Write(float val);
		CustomRpcSender *Write(const std::wstring &val);
		CustomRpcSender *Write(unsigned long long val);
		CustomRpcSender *Write(int val);
		CustomRpcSender *Write(unsigned int val);
		CustomRpcSender *Write(unsigned short val);
		CustomRpcSender *Write(unsigned char val);
		CustomRpcSender *Write(signed char val);
		CustomRpcSender *Write(bool val);
		CustomRpcSender *Write(Il2CppStructArray<unsigned char> *bytes);
		CustomRpcSender *Write(Il2CppStructArray<unsigned char> *bytes, int offset, int length);
		CustomRpcSender *WriteBytesAndSize(Il2CppStructArray<unsigned char> *bytes);
		CustomRpcSender *WritePacked(int val);
		CustomRpcSender *WritePacked(unsigned int val);
		CustomRpcSender *WriteNetObject(InnerNetObject *obj);
//		#endregion

	private:
		CustomRpcSender *Write(std::function<void(MessageWriter*)> action);

	public:
		enum class State
		{
			BeforeInit = 0, //初期化前 何もできない
			Ready, //送信準備完了 StartMessageとSendMessageを実行可能
			InRootMessage, //StartMessage～EndMessageの間の状態 StartRpcとEndMessageを実行可能
			InRpc, //StartRpc～EndRpcの間の状態 WriteとEndRpcを実行可能
			Finished //送信後 何もできない
		};
	};

	class CustomRpcSenderExtensions final
	{
	public:
		static void RpcSetRole(CustomRpcSender *sender, PlayerControl *player, RoleTypes *role, int targetClientId = -1);
		static void RpcMurderPlayer(CustomRpcSender *sender, PlayerControl *player, PlayerControl *target, int targetClientId = -1);
	};
}
