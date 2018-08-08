#pragma once

#include "Source/Developer/Utils/FileSystem.h"
#include "Source/Developer/Utils/Log.h"


namespace Skel
{
	class SKEL_API BuildTool
	{
	public:
		static void CreateProject(EAString Name);
		static void CreateBuildProjectFile(EAString EnginePath, EAString ProjectName, EAString ProjectSolution);
		static void GenerateVSProject(EAString filePath);
		static void CompileProject(EAString path, EAString ProjectName);
		static void CreateEProject(EAString path, EAString ProjectName);
	};
}