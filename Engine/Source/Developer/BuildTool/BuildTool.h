#pragma once

#include "Source/Developer/Utils/FileSystem.h"
#include "Source/Developer/Utils/Log.h"

#include <json.hpp>

using json = nlohmann::json;

namespace Skel
{
	class SKEL_API BuildTool
	{
	public:
		static void CreateProject(EAString Name, EAString Path);
		static void CreateBuildProjectFile(EAString EnginePath, EAString ProjectName, EAString ProjectSolution, EAString ProjectPath);
		static void GenerateVSProject(EAString filePath, EAString dirPath, EAString projectNmae);
		static void CompileProject(EAString path, EAString ProjectName);
		static void CreateSKProject(EAString path, EAString ProjectName);
		static nlohmann::json ReadSKProject(EAString path);
	};
}