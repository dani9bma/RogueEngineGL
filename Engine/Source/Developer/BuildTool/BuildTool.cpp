#include "BuildTool.h"
#include <fstream>
#include <iomanip>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
using json = nlohmann::json;

namespace Skel
{
	//Refactor this code
	void BuildTool::CreateProject(EAString Name, EAString path)
	{
		char currentDir[1024];
		GetCurrentDir(currentDir, sizeof(currentDir));
		
		EAString EnginePath = "\@";
		EnginePath.append("\"");
		EnginePath.append(currentDir);

		if (EnginePath.find("binaries") < EnginePath.length())
		{
			EnginePath.replace(EnginePath.find("binaries"), EnginePath.find("binaries"), "");
			EnginePath.append("Engine");
		}
		EnginePath.append("\"");

		EAString ProjectName = Name;

		EAString ProjectSolution = ProjectName + "Solution";

		EAString sub = "\\\\";
		if (path.find(sub) < path.length())
		{
			path.replace(path.find(sub), sub.length(), "\\");
			path.append("\\");
		}

		CreateBuildProjectFile(EnginePath, ProjectName, ProjectSolution, path);
	}

	void BuildTool::CreateBuildProjectFile(EAString EnginePath, EAString ProjectName, EAString ProjectSolution, EAString ProjectPath)
	{
		EAString EnginePathTag = "{enginepath}";
		EAString ProjectNameTag = "{projectname}";
		EAString ProjectSolutionTag = "{projectsolution}";

		EAString result;
		EAString mainPath = EnginePath;
		mainPath.replace(mainPath.find("\""), mainPath.find("\""), "");
		mainPath.replace(mainPath.find("\""), mainPath.find("\""), "");
		mainPath.replace(0, 1, "");
		FileSystem::ReadFile(mainPath + "\\build\\project.sharpmake.template", result);

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
		EAString filePath = ProjectPath + ProjectName + "\\Build\\build.sharpmake.cs";
		EAString dirPath = ProjectPath + ProjectName;

#if defined(_WIN32) || defined(_WIN64)
		EAString path = dirPath;
		CreateDirectory(path.c_str(), NULL);
		path.append("\\Build\\");
		CreateDirectory(path.c_str(), NULL);
		path = ProjectPath + ProjectName + "\\Source\\";
		CreateDirectory(path.c_str(), NULL);
#endif

		FileSystem::WriteFile(filePath, result);

		FileSystem::ReadFile(mainPath + "\\build\\class.cpp.template", result);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		FileSystem::WriteFile(path + ProjectName + ".cpp", result);

		FileSystem::ReadFile(mainPath + "\\build\\class.h.template", result);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		result.replace(result.find(ProjectNameTag), ProjectNameTag.length(), ProjectName);
		FileSystem::WriteFile(path + ProjectName + ".h", result);

		GenerateVSProject(filePath);
		CompileProject(dirPath, ProjectName);
		CreateSKProject(dirPath, ProjectName);
	}

	void BuildTool::GenerateVSProject(EAString filePath)
	{
#if defined(_WIN32) || defined(_WIN64)
		EAString command = "cd Build && dir && build_win.bat ";
		command.append(filePath);
		system(command.c_str());
#endif
	}

	void BuildTool::CompileProject(EAString path, EAString ProjectName)
	{
#if defined(_WIN32) || defined(_WIN64)
		EAString command = "cd ";
		command.append(path);
		command.append(" && msbuild.exe ");
		command.append(ProjectName);
		command.append(".vcxproj");
		SK_LOGP(Error, System, "%s", command.c_str());
		system(command.c_str());
#endif
	}

	void BuildTool::CreateSKProject(EAString path, EAString ProjectName)
	{
		json j;

		j["name"] = ProjectName.c_str();
		EAString dllPath = path + "\\binaries\\" + ProjectName + ".dll";
		j["dll"] = dllPath.c_str();

		EAString file = path + "\\";
		file.append(ProjectName);
		file.append(".skproject");

		std::ofstream o(file.c_str());
		o << std::setw(4) << j << std::endl;
	}

	nlohmann::json BuildTool::ReadSKProject(EAString path)
	{
		json j;

		std::ifstream i(path.c_str());
		i >> j;

		return j;
	}

}