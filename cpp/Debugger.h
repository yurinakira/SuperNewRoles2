#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "stringhelper.h"
#include "tangible_filesystem.h"

//C# TO C++ CONVERTER TODO TASK: C# to C++ Converter could not confirm whether this is a namespace alias or a type alias:
//using LogLevel = BepInEx::Logging::LogLevel;

namespace SuperNewRoles
{
	/*
	class Webhook
	{
	    public static void Send(string text)
	    {
	        if (Main.WebhookURL.Value == "none") return;
	        HttpClient httpClient = new();
	        Dictionary<string, string> strs = new()
	        {
	            { "content", text },
	            { "username", "TownOfHost-Debugger" },
	            { "avatar_url", "https://cdn.discordapp.com/avatars/336095904320716800/95243b1468018a24f7ae03d7454fd5f2.webp?size=40" }
	        };
	        TaskAwaiter<HttpResponseMessage> awaiter = httpClient.PostAsync(
	            Main.WebhookURL.Value, new FormUrlEncodedContent(strs)).GetAwaiter();
	        awaiter.GetResult();
	    }
	}
	*/
	class Logger
	{
	public:
		static bool isEnable;
		static std::vector<std::wstring> disableList;
		static std::vector<std::wstring> sendToGameList;
		static bool isDetail;
		static bool isAlsoInGame;
		static void Enable();
		static void Disable();
		static void Enable(const std::wstring &tag, bool toGame = false);
		static void Disable(const std::wstring &tag);
		static void SendInGame(const std::wstring &text, bool isAlways = false);
	private:
		static void SendToFile(const std::wstring &text, BepInEx::Logging::LogLevel *level = BepInEx::Logging::LogLevel::Info, const std::wstring &tag = L"", int lineNumber = 0, const std::wstring &fileName = L"");
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Info(string text, string tag, [CallerLineNumber] int lineNumber = 0, [CallerFilePath] string fileName = "")
		static void Info(const std::wstring &text, const std::wstring &tag, int lineNumber = 0, const std::wstring &fileName = L"");
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Warn(string text, string tag, [CallerLineNumber] int lineNumber = 0, [CallerFilePath] string fileName = "")
		static void Warn(const std::wstring &text, const std::wstring &tag, int lineNumber = 0, const std::wstring &fileName = L"");
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Error(string text, string tag, [CallerLineNumber] int lineNumber = 0, [CallerFilePath] string fileName = "")
		static void Error(const std::wstring &text, const std::wstring &tag, int lineNumber = 0, const std::wstring &fileName = L"");
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Fatal(string text, string tag, [CallerLineNumber] int lineNumber = 0, [CallerFilePath] string fileName = "")
		static void Fatal(const std::wstring &text, const std::wstring &tag, int lineNumber = 0, const std::wstring &fileName = L"");
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Msg(string text, string tag, [CallerLineNumber] int lineNumber = 0, [CallerFilePath] string fileName = "")
		static void Msg(const std::wstring &text, const std::wstring &tag, int lineNumber = 0, const std::wstring &fileName = L"");
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void CurrentMethod([CallerLineNumber] int lineNumber = 0, [CallerFilePath] string fileName = "")
		static void CurrentMethod(int lineNumber = 0, const std::wstring &fileName = L"");
	};
}
