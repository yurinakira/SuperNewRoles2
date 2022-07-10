#include "Debugger.h"
#include "Main.h"
#include "Config.h"

namespace SuperNewRoles
{

bool Logger::isEnable = false;
std::vector<std::wstring> Logger::disableList;
std::vector<std::wstring> Logger::sendToGameList;
bool Logger::isDetail = false;
bool Logger::isAlsoInGame = false;

	void Logger::Enable()
	{
		isEnable = true;
	}

	void Logger::Disable()
	{
		isEnable = false;
	}

	void Logger::Enable(const std::wstring &tag, bool toGame)
	{
		disableList.Remove(tag);
		if (toGame && !std::find(sendToGameList.begin(), sendToGameList.end(), tag) != sendToGameList.end())
		{
			sendToGameList.push_back(tag);
		}
		else
		{
			sendToGameList.Remove(tag);
		}
	}

	void Logger::Disable(const std::wstring &tag)
	{
		if (!std::find(disableList.begin(), disableList.end(), tag) != disableList.end())
		{
			disableList.push_back(tag);
		}
	}

	void Logger::SendInGame(const std::wstring &text, bool isAlways)
	{
		if (!isEnable)
		{
			return;
		}
		if (DestroyableSingleton<HudManager*>::_instance)
		{
			DestroyableSingleton<HudManager*>::Instance->Notifier.AddItem(text);
		}
	}

	void Logger::SendToFile(const std::wstring &text, BepInEx::Logging::LogLevel *level, const std::wstring &tag, int lineNumber, const std::wstring &fileName)
	{
		if (!isEnable || std::find(disableList.begin(), disableList.end(), tag) != disableList.end())
		{
			return;
		}
		auto logger = SuperNewRolesPlugin::Logger;
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		std::wstring t = DateTime::Now.ToString(L"HH:mm:ss");
		if (std::find(sendToGameList.begin(), sendToGameList.end(), tag) != sendToGameList.end() || isAlsoInGame)
		{
			SendInGame(StringHelper::formatSimple(L"[{0}]{1}", tag, text));
		}
		text = StringHelper::replace(StringHelper::replace(text, L"\r", L"\\r"), L"\n", L"\\n");
		std::wstring log_text = StringHelper::formatSimple(L"[{0}][{1}]{2}", t, tag, text);
		if (isDetail && ConfigRoles::getDebugMode()->Value)
		{
			StackFrame *stack = new StackFrame(2);
			std::wstring className = stack->GetMethod()->ReflectedType.name();
			std::wstring memberName = stack->GetMethod()->Name;
//C# TO C++ CONVERTER TODO TASK: String.Format is not converted to C++ if more than 3 data arguments of different types are specified:
			log_text = std::wstring::Format(L"[{0}][{1}.{2}({3}:{4})][{5}]{6}", t, className, memberName, FileSystem::getFileName(fileName), lineNumber, tag, text);

			delete stack;
		}
		switch (level)
		{
			case BepInEx::Logging::LogLevel::Info:
				logger->LogInfo(log_text);
				break;
			case BepInEx::Logging::LogLevel::Warning:
				logger->LogWarning(log_text);
				break;
			case BepInEx::Logging::LogLevel::Error:
				logger->LogError(log_text);
				break;
			case BepInEx::Logging::LogLevel::Fatal:
				logger->LogFatal(log_text);
				break;
			case BepInEx::Logging::LogLevel::Message:
				logger->LogMessage(log_text);
				break;
			default:
				logger->LogWarning(L"Error:Invalid LogLevel");
				logger->LogInfo(log_text);
				break;
		}
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Info(string text, string tag, [CallerLineNumber] int lineNumber = 0, [CallerFilePath] string fileName = "")
	void Logger::Info(const std::wstring &text, const std::wstring &tag, int lineNumber, const std::wstring &fileName)
	{
		SendToFile(text, BepInEx::Logging::LogLevel::Info, tag, lineNumber, fileName);
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Warn(string text, string tag, [CallerLineNumber] int lineNumber = 0, [CallerFilePath] string fileName = "")
	void Logger::Warn(const std::wstring &text, const std::wstring &tag, int lineNumber, const std::wstring &fileName)
	{
		SendToFile(text, BepInEx::Logging::LogLevel::Warning, tag, lineNumber, fileName);
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Error(string text, string tag, [CallerLineNumber] int lineNumber = 0, [CallerFilePath] string fileName = "")
	void Logger::Error(const std::wstring &text, const std::wstring &tag, int lineNumber, const std::wstring &fileName)
	{
		SendToFile(text, BepInEx::Logging::LogLevel::Error, tag, lineNumber, fileName);
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Fatal(string text, string tag, [CallerLineNumber] int lineNumber = 0, [CallerFilePath] string fileName = "")
	void Logger::Fatal(const std::wstring &text, const std::wstring &tag, int lineNumber, const std::wstring &fileName)
	{
		SendToFile(text, BepInEx::Logging::LogLevel::Fatal, tag, lineNumber, fileName);
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Msg(string text, string tag, [CallerLineNumber] int lineNumber = 0, [CallerFilePath] string fileName = "")
	void Logger::Msg(const std::wstring &text, const std::wstring &tag, int lineNumber, const std::wstring &fileName)
	{
		SendToFile(text, BepInEx::Logging::LogLevel::Message, tag, lineNumber, fileName);
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void CurrentMethod([CallerLineNumber] int lineNumber = 0, [CallerFilePath] string fileName = "")
	void Logger::CurrentMethod(int lineNumber, const std::wstring &fileName)
	{
		StackFrame *stack = new StackFrame(1);
//C# TO C++ CONVERTER TODO TASK: String.Format is not converted to C++ if more than 3 data arguments of different types are specified:
		Logger::Msg(std::wstring::Format(L"\"{0}.{1}\" Called in \"{2}({3})\"", stack->GetMethod()->ReflectedType.name(), stack->GetMethod()->Name, FileSystem::getFileName(fileName), lineNumber), L"Method");

		delete stack;
	}
}
