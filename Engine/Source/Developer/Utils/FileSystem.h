#pragma once

#include "../Common/Defines.h"
#include "../Common/Types.h"
#include <EASTL/string.h>

namespace Skel
{
	class SKEL_API FileSystem
	{
	public:
		inline static void PrintToLogFile(EAString text)
		{
			FILE* file = fopen("../Engine/log/log.txt", "a");
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
