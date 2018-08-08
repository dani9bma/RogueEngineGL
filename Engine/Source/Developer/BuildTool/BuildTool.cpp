#include "BuildTool.h"

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace Skel
{
	//Refactor this code
	void BuildTool::CreateProject(EAString Name)
	{
		char path[1024];
		GetCurrentDir(path, sizeof(path));

		EAString remove = "Engine\Source\Developer\BuildTool";
		EAString EnginePath = "\@";
		EnginePath.append("\"");
		EnginePath.append(path);
		EnginePath.append("\"");

		EAString ProjectName = Name;
		EAString ProjectSolution = ProjectName + "Solution";

		CreateBuildProjectFile(EnginePath, ProjectName, ProjectSolution);
	}

	void BuildTool::CreateBuildProjectFile(EAString EnginePath, EAString ProjectName, EAString ProjectSolution)
	{
		EAString EnginePathTag = "{enginepath}";
		EAString ProjectNameTag = "{projectname}";
		EAString ProjectSolutionTag = "{projectsolution}";

		EAString result;
		FileSystem::ReadFile("build/project.sharpmake.template", result);

		result.replace(result.find("(end)"), result.length(), "");

		result.replace(result.find(EnginePathTag), EnginePathTag.length(), EnginePath);
		result.replace(result.find(EnginePathTag), EnginePathTag.length(), EnginePath);
		result.replace(result.find(EnginePathTag), EnginePathTag.length(), EnginePath);
		result.replace(result.find(EnginePathTag), EnginePathTag.length(), EnginePath);
		result.replace(result.find(EnginePathTag), EnginePathTag.length(), EnginePath);
		result.replace(result.find(EnginePathTag), EnginePathTag.length(), EnginePath);
		result.replace(result.find(EnginePathTag), EnginePathTag.length(), EnginePath);
		result.replace(result.find(EnginePathTag), EnginePathTag.length(), EnginePath);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		result.replace(result.find(ProjectSolutionTag), ProjectSolutionTag.length(), ProjectSolution);
		result.replace(result.find(ProjectSolutionTag), ProjectSolutionTag.length(), ProjectSolution);
		result.replace(result.find(ProjectSolutionTag), ProjectSolutionTag.length(), ProjectSolution);
		EAString filePath = "../../../SkelProjects/" + ProjectName + "/Build/build.sharpmake.cs";
		EAString dirPath = "../../../SkelProjects/" + ProjectName;

#if defined(_WIN32) || defined(_WIN64)
		CreateDirectory(dirPath.c_str(), NULL);
		dirPath.append("/Build/");
		CreateDirectory(dirPath.c_str(), NULL);
		dirPath = "../../../SkelProjects/" + ProjectName + "/Source";
		CreateDirectory(dirPath.c_str(), NULL);
#endif

		FileSystem::WriteFile(filePath, result);
		GenerateVSProject(filePath);
	}

	void BuildTool::GenerateVSProject(EAString filePath)
	{
#if defined(_WIN32) || defined(_WIN64)
		EAString path = "../" + filePath;
		EAString command = "cd Build && build_win.bat ";
		command.append(path);
		system(command.c_str());
#endif
	}

}