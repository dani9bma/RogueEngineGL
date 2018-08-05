#pragma once

#include "../Common/Types.h"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#include <cstdarg>
#include "FileSystem.h"

namespace Skel
{
	enum LogLevel
	{
		Info,
		Warning,
		Error
	};

	enum LogModule
	{
		System,
		Rendering,
		Input
	};

	class Log
	{
	public:
		inline static EAString LogLevelToString(const LogLevel logLevel)
		{
			switch(logLevel)
			{
			case LogLevel::Info:
				return EAString("Info] ");
			case LogLevel::Warning:
				return EAString("Warning] ");
			case LogLevel::Error:
				return EAString("Error] ");
			default:
				return EAString("Info");
			}
		}

		inline static EAString LogModuleToString(const LogModule logModule)
		{
			switch (logModule)
			{
			case LogModule::System:
				return EAString("[System|");
			case LogModule::Rendering:
				return EAString("[Rendering|");
			case LogModule::Input:
				return EAString("[Input|");
			default:
				return EAString("[NoModule|");
			}
		}

#if defined(_WIN32) || defined(_WIN64)

		inline static void PrintLogLevelColor(const LogLevel logLevel)
		{
			const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			switch (logLevel)
			{
			case LogLevel::Info:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				break;
			case LogLevel::Warning:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			case LogLevel::Error:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				
			}
		}

		inline static void PlatformLogP(const LogLevel logLevel, LogModule logModule, EAString buffer)
		{
			SYSTEMTIME time;
			GetSystemTime(&time);

			char date[1024];
			sprintf(date, "[%02d/%02d/%d]", time.wDay, time.wMonth, time.wYear);

			char year[1024];
			sprintf(year, "[%02d:%02d]", time.wHour, time.wMinute);

			EAString txt = date;
			txt.append(year);
			txt.append(LogModuleToString(logModule));
			txt.append(LogLevelToString(logLevel));
			txt.append(buffer);
			txt.append("\n");


			PrintLogLevelColor(logLevel);

			OutputDebugString(txt.c_str());
			FileSystem::PrintToLogFile(txt.c_str());

			PrintLogLevelColor(LogLevel::Info);
		}

		inline static void PlatformLogPNoFile(const LogLevel logLevel, LogModule logModule, EAString buffer)
		{
			SYSTEMTIME time;
			GetSystemTime(&time);

			char date[1024];
			sprintf(date, "[%02d/%02d/%d]", time.wDay, time.wMonth, time.wYear);

			char year[1024];
			sprintf(year, "[%02d:%02d]", time.wHour, time.wMinute);

			EAString txt = date;
			txt.append(year);
			txt.append(LogModuleToString(logModule));
			txt.append(LogLevelToString(logLevel));
			txt.append(buffer);
			txt.append("\n");


			PrintLogLevelColor(logLevel);

			OutputDebugString(txt.c_str());

			PrintLogLevelColor(LogLevel::Info);
		}

		inline static void PlatformLog(LogLevel logLevel, LogModule logModule, EAString text)
		{
			SYSTEMTIME time;
			GetSystemTime(&time);

			char date[1024];
			sprintf(date, "[%02d/%02d/%d]", time.wDay, time.wMonth, time.wYear);

			char year[1024];
			sprintf(year, "[%02d:%02d]", time.wHour, time.wMinute);

			EAString txt = date;
			txt.append(year);
			txt.append(LogModuleToString(logModule));
			txt.append(LogLevelToString(logLevel));
			txt.append(text);
			txt.append("\n");


			PrintLogLevelColor(logLevel);

			OutputDebugString(txt.c_str());
			FileSystem::PrintToLogFile(txt.c_str());
			

			PrintLogLevelColor(LogLevel::Info);
		}

		inline static void PlatformLogNoFile(LogLevel logLevel, LogModule logModule, EAString text)
		{
			SYSTEMTIME time;
			GetSystemTime(&time);

			char date[1024];
			sprintf(date, "[%02d/%02d/%d]", time.wDay, time.wMonth, time.wYear);

			char year[1024];
			sprintf(year, "[%02d:%02d]", time.wHour, time.wMinute);

			EAString txt = date;
			txt.append(year);
			txt.append(LogModuleToString(logModule));
			txt.append(LogLevelToString(logLevel));
			txt.append(text);
			txt.append("\n");


			PrintLogLevelColor(logLevel);

			OutputDebugString(txt.c_str());


			PrintLogLevelColor(LogLevel::Info);
		}
#else

		/*			foreground  background
		black        30         40
		red          31         41
		green        32         42
		yellow       33         43
		blue         34         44
		magenta      35         45
		cyan         36         46
		white        37         47
		
		*/
inline static void PrintLogLevelColor(const LogLevel logLevel, EAString text)
{
	switch (logLevel)
	{
	case LogLevel::Info:
		text.append("\033[1;0");
		break;
	case LogLevel::Warning:
		text.append("\033[1;33");
		break;
	case LogLevel::Error:
		text.append("\033[1;31");

	}
}


		inline static void PlatformLogP(const LogLevel logLevel, LogModule logModule, EAString buffer)
		{

			char time[10];
			_strtime(time);

			char date[10];
			_strdate(date);

			EAString txt;

			PrintLogLevelColor(logLevel, txt);
			
			txt.append(date);
			txt.append(year);
			txt.append(LogModuleToString(logModule));
			txt.append(LogLevelToString(logLevel));
			txt.append(buffer);
			txt.append("\n");


			printf(txt.c_str());
			FileSystem::PrintToLogFile(txt.c_str());

			PrintLogLevelColor(LogLevel::Info);
		}

		inline static void PlatformLogPNoFile(const LogLevel logLevel, LogModule logModule, EAString buffer)
		{
			char time[10];
			_strtime(time);

			char date[10];
			_strdate(date);

			EAString txt;

			PrintLogLevelColor(logLevel, txt);

			txt.append(date);

			txt.append(year);
			txt.append(LogModuleToString(logModule));
			txt.append(LogLevelToString(logLevel));
			txt.append(buffer);
			txt.append("\n");



			printf(txt.c_str());

			PrintLogLevelColor(LogLevel::Info);
		}

		inline static void PlatformLog(LogLevel logLevel, LogModule logModule, EAString text)
		{
			char time[10];
			_strtime(time);

			char date[10];
			_strdate(date);

			EAString txt;

			PrintLogLevelColor(logLevel, txt);

			txt.append(date);

			txt.append(year);
			txt.append(LogModuleToString(logModule));
			txt.append(LogLevelToString(logLevel));
			txt.append(text);
			txt.append("\n");



			printf(txt.c_str());
			FileSystem::PrintToLogFile(txt.c_str());


			PrintLogLevelColor(LogLevel::Info);
		}

		inline static void PlatformLogNoFile(LogLevel logLevel, LogModule logModule, EAString text)
		{
			char time[10];
			_strtime(time);

			char date[10];
			_strdate(date);

			EAString txt;

			PrintLogLevelColor(logLevel, txt);

			txt.append(date);

			txt.append(year);
			txt.append(LogModuleToString(logModule));
			txt.append(LogLevelToString(logLevel));
			txt.append(text);
			txt.append("\n");

			printf(txt.c_str());


			PrintLogLevelColor(LogLevel::Info);
		}
#endif

	};
}


/**
 * \brief
 * \param logLevel
 * \param logModule
 * \param txt
 * \param ... args
 * \Example: LOG_P(Skel::LogLevel::Warning, Skel::LogModule::System, "%s and %s", string->c_str(), "hello") -> [22/07/2018] [22:28] Hello World and hello
 */
#define SK_LOGP(logLevel, logModule, txt,  ...) \
	{ \
	char buf[1024]; \
	sprintf(buf, txt, __VA_ARGS__); \
	Skel::Log::PlatformLogP(logLevel, logModule, buf); \
	}\

#define SK_LOGPNF(logLevel, logModule, txt,  ...) \
	{ \
	char buf[1024]; \
	sprintf(buf, txt, __VA_ARGS__); \
	Skel::Log::PlatformLogPNoFile(logLevel, logModule, buf); \
	}\

 /**
 * \brief
 * \param logLevel
 * \param logModule
 * \param txt
 * \Example: LOG(Skel::LogLevel::Error, Skel::LogModule::System, "rip") -> [22/07/2018] [22:15] rip
 */
#define SK_LOG(logLevel, logModule, txt) \
	Skel::Log::PlatformLog(logLevel, logModule, txt);\

#define SK_LOGNF(logLevel, logModule, txt) \
	Skel::Log::PlatformLogNoFile(logLevel, logModule, txt);\


