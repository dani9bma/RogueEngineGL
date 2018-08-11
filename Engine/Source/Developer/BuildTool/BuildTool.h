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
		static void CreateProject(SKString Name, SKString Path);
		static void CreateBuildProjectFile(SKString EnginePath, SKString ProjectName, SKString ProjectSolution, SKString ProjectPath);
		static void GenerateVSProject(SKString filePath, SKString dirPath, SKString projectName, SKString EnginePath);
		static void CompileProject(SKString path, SKString ProjectName);
		static void CreateSKProject(SKString path, SKString ProjectName);
		static nlohmann::json ReadSKProject(SKString path);
	};
}