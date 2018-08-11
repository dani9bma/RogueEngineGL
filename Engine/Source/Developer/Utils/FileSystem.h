#pragma once

#include "../Common/Defines.h"
#include "../Common/Types.h"


#include <filesystem>
#include <fstream>
#include <sstream>

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
		inline static SKString GetEnginePath()
		{
			char d[1024];
			GetCurrentDir(d, sizeof(d));
			SKString EnginePath = d;
			if (EnginePath.find("binaries") < EnginePath.length())
			{
				EnginePath.replace(EnginePath.find("binaries"), EnginePath.find("binaries"), "");
				EnginePath.append("Engine");
			}

			return EnginePath;
		}

		inline static SKString LoadResource(SKString path)
		{
			char currentDir[1024];
			GetCurrentDir(currentDir, sizeof(currentDir));

			SKString EnginePath;

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

		inline static void PrintToLogFile(SKString text)
		{
			struct stat buffer;
			if (stat("Log", &buffer) == 0)
				std::experimental::filesystem::create_directory("Log");

			FILE* file = fopen("Log/log.txt", "a");
			fprintf(file, text.c_str());
			fclose(file);
		}

		inline static void ReadFile(SKString path, SKString& result)
		{
			std::ifstream in(path);
			std::stringstream buffer;
			buffer << in.rdbuf();
			std::string contents(buffer.str());

			result = contents;
		}

		inline static void WriteFileAppend(SKString path, SKString text)
		{
			std::ofstream o(path.c_str(), std::ofstream::app);
			o << text << std::endl;
		}

		inline static void WriteFile(SKString path, SKString text)
		{
			std::ofstream o(path.c_str());
			o << text << std::endl;
		}
	};
}
