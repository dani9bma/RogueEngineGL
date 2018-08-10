#pragma once

#include "../Common/Defines.h"
#include "../Common/Types.h"

#include <EASTL/string.h>
#include <filesystem>

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace Skel
{
	class SKEL_API FileSystem
	{
	public:
		inline static EAString LoadResource(EAString path)
		{
			char currentDir[1024];
			GetCurrentDir(currentDir, sizeof(currentDir));

			EAString EnginePath;

			EnginePath.append(currentDir);

			if (EnginePath.find("binaries") < EnginePath.length())
			{
				EnginePath.replace(EnginePath.find("binaries"), EnginePath.find("binaries"), "");
				EnginePath.append("Engine");
			}
			EnginePath.append("\\");
			EnginePath.append("Content\\");
			EnginePath.append(path);
			return EnginePath;
		}

		inline static void PrintToLogFile(EAString text)
		{
			struct stat buffer;
			if (stat("Log", &buffer) == 0)
				std::experimental::filesystem::create_directory("Log");

			FILE* file = fopen("Log/log.txt", "a");
			fprintf(file, text.c_str());
			fclose(file);
		}

		inline static void ReadFile(EAString path, EAString& result)
		{
			FILE* file = fopen(path.c_str(), "r");
			if (file == nullptr)
				return;

			fseek(file, 0, SEEK_END);
			int32 length = ftell(file);
			EAString res(length, 0);
			fseek(file, 0, SEEK_SET);
			fread(&res[0], 1, length, file);
			fclose(file);

			result = res.c_str();
		}

		inline static void ReadFileNoNewLine(EAString path, EAString& result)
		{
			FILE* file = fopen(path.c_str(), "r");
			if (file == nullptr)
				return;

			fseek(file, 0, SEEK_END);
			int32 length = ftell(file);
			EAString res(length, 0);
			fseek(file, 0, SEEK_SET);
			fread(&res[0], 1, length, file);
			fclose(file);

			res.erase(eastl::remove(res.begin(), res.end(), '\n'), res.end());
			result = res.c_str();
		}

		inline static void WriteFileAppend(EAString path, EAString text)
		{
			FILE* file = fopen(path.c_str(), "a");
			fprintf(file, text.c_str());
			fclose(file);
		}

		inline static void WriteFileAppendNewLine(EAString path, EAString text)
		{
			FILE* file = fopen(path.c_str(), "a");
			text.append("\n");
			fprintf(file, text.c_str());
			fclose(file);
		}

		inline static void WriteFile(EAString path, EAString text)
		{
			FILE* file = fopen(path.c_str(), "w");
			fprintf(file, text.c_str());
			fclose(file);
		}
	};
}
