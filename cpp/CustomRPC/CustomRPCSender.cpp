//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "CustomRPCSender.h"
#include "../Debugger.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace UnhollowerBaseLib;

namespace SuperNewRoles
{

	CustomRpcSender::CustomRpcSender()
	{
	}

	CustomRpcSender::CustomRpcSender(const std::wstring &name, SendOption *sendOption, bool isUnsafe) : name(name), sendOption(sendOption)
	{
		stream = MessageWriter::Get(sendOption);

		this->isUnsafe = isUnsafe;
		this->currentRpcTarget = -2;
		onSendDelegate = [&] ()
		{
			Logger::Info(StringHelper::formatSimple(L"{0}'s onSendDelegate =>", this->name), L"CustomRpcSender");
		};

		currentState = State::Ready;
		Logger::Info(StringHelper::formatSimple(L"\"{0}\" is ready", name), L"CustomRpcSender");
	}

	CustomRpcSender *CustomRpcSender::Create(const std::wstring &name, SendOption *sendOption, bool isUnsafe)
	{
		return new CustomRpcSender(name, sendOption, isUnsafe);
	}

	CustomRpcSender *CustomRpcSender::StartMessage(int targetClientId)
	{
		if (currentState != State::Ready)
		{
			std::wstring errorMsg = StringHelper::formatSimple(L"Messageを開始しようとしましたが、StateがReadyではありません (in: \"{0}\") (State: \"{1}\")", name, currentState);
			if (isUnsafe)
			{
				Logger::Warn(errorMsg, L"CustomRpcSender.Warn");
			}
			else
			{
				throw InvalidOperationException(StringHelper::wstring_to_string(errorMsg));
			}
		}

		if (targetClientId < 0)
		{
			// 全員に対するRPC
			stream->StartMessage(5);
			stream->Write(AmongUsClient::Instance->GameId);
		}
		else
		{
			// 特定のクライアントに対するRPC (Desync)
			stream->StartMessage(6);
			stream->Write(AmongUsClient::Instance->GameId);
			stream->WritePacked(targetClientId);
		}

		currentRpcTarget = targetClientId;
		currentState = State::InRootMessage;
		return this;
	}

	CustomRpcSender *CustomRpcSender::EndMessage(int targetClientId)
	{
		if (currentState != State::InRootMessage)
		{
			std::wstring errorMsg = StringHelper::formatSimple(L"Messageを終了しようとしましたが、StateがInRootMessageではありません (in: \"{0}\")", name);
			if (isUnsafe)
			{
				Logger::Warn(errorMsg, L"CustomRpcSender.Warn");
			}
			else
			{
				throw InvalidOperationException(StringHelper::wstring_to_string(errorMsg));
			}
		}
		stream->EndMessage();

		currentRpcTarget = -2;
		currentState = State::Ready;
		return this;
	}

	CustomRpcSender *CustomRpcSender::StartRpc(unsigned int targetNetId, RpcCalls *rpcCall)
	{
		return StartRpc(targetNetId, static_cast<unsigned char>(rpcCall));
	}

	CustomRpcSender *CustomRpcSender::StartRpc(unsigned int targetNetId, unsigned char callId)
	{
		if (currentState != State::InRootMessage)
		{
			std::wstring errorMsg = StringHelper::formatSimple(L"RPCを開始しようとしましたが、StateがInRootMessageではありません (in: \"{0}\")", name);
			if (isUnsafe)
			{
				Logger::Warn(errorMsg, L"CustomRpcSender.Warn");
			}
			else
			{
				throw InvalidOperationException(StringHelper::wstring_to_string(errorMsg));
			}
		}

		stream->StartMessage(2);
		stream->WritePacked(targetNetId);
		stream->Write(callId);

		currentState = State::InRpc;
		return this;
	}

	CustomRpcSender *CustomRpcSender::EndRpc()
	{
		if (currentState != State::InRpc)
		{
			std::wstring errorMsg = StringHelper::formatSimple(L"RPCを終了しようとしましたが、StateがInRpcではありません (in: \"{0}\")", name);
			if (isUnsafe)
			{
				Logger::Warn(errorMsg, L"CustomRpcSender.Warn");
			}
			else
			{
				throw InvalidOperationException(StringHelper::wstring_to_string(errorMsg));
			}
		}

		stream->EndMessage();
		currentState = State::InRootMessage;
		return this;
	}

	CustomRpcSender *CustomRpcSender::AutoStartRpc(unsigned int targetNetId, unsigned char callId, int targetClientId)
	{
		if (targetClientId == -2)
		{
			targetClientId = -1;
		}
		if (currentState != State::Ready && currentState != State::InRootMessage)
		{
			std::wstring errorMsg = StringHelper::formatSimple(L"RPCを自動で開始しようとしましたが、StateがReadyまたはInRootMessageではありません (in: \"{0}\")", name);
			if (isUnsafe)
			{
				Logger::Warn(errorMsg, L"CustomRpcSender.Warn");
			}
			else
			{
				throw InvalidOperationException(StringHelper::wstring_to_string(errorMsg));
			}
		}
		if (currentRpcTarget != targetClientId)
		{
			//StartMessage処理
			if (currentState == State::InRootMessage)
			{
				this->EndMessage();
			}
			this->StartMessage(targetClientId);
		}
		this->StartRpc(targetNetId, callId);

		return this;
	}

	void CustomRpcSender::SendMessage()
	{
		if (currentState == State::InRootMessage)
		{
			this->EndMessage();
		}
		if (currentState != State::Ready)
		{
			std::wstring errorMsg = StringHelper::formatSimple(L"RPCを送信しようとしましたが、StateがReadyではありません (in: \"{0}\")", name);
			if (isUnsafe)
			{
				Logger::Warn(errorMsg, L"CustomRpcSender.Warn");
			}
			else
			{
				throw InvalidOperationException(StringHelper::wstring_to_string(errorMsg));
			}
		}

		AmongUsClient::Instance->SendOrDisconnect(stream);
		onSendDelegate();
		currentState = State::Finished;
		Logger::Info(StringHelper::formatSimple(L"\"{0}\" is finished", name), L"CustomRpcSender");
		stream->Recycle();
	}

	CustomRpcSender *CustomRpcSender::Write(float val)
	{
		return Write([&] (std::any w)
		{

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
