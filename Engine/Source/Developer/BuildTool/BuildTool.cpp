#include "BuildTool.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

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
	void BuildTool::CreateProject(SKString Name, SKString path)
	{
		char currentDir[1024];
		GetCurrentDir(currentDir, sizeof(currentDir));

		SKString ProjectPath = path;
		SKString EnginePath = "";
		EnginePath.append(currentDir);

		if (EnginePath.find("binaries") < EnginePath.length())
		{
			EnginePath.replace(EnginePath.find("binaries"), EnginePath.find("binaries"), "");
			EnginePath.append("Engine");
		}

		SKString ProjectName = Name;

		SKString ProjectSolution = ProjectName + "Solution";

		SKString sub = "\\\\";
		if (ProjectPath.find(sub) < ProjectPath.length())
		{
			ProjectPath.replace(path.find(sub), sub.length(), "\\");
			ProjectPath.append("\\");
		}

		CreateBuildProjectFile(EnginePath, ProjectName, ProjectSolution, ProjectPath);
	}

	void BuildTool::CreateBuildProjectFile(SKString EnginePath, SKString ProjectName, SKString ProjectSolution, SKString ProjectPath)
	{
		SKString EnginePathTag = "{enginepath}";
		SKString ProjectNameTag = "{projectname}";
		SKString ProjectSolutionTag = "{projectsolution}";

		SKString result;
		SKString mainPath = EnginePath;
		FileSystem::ReadFile(mainPath + "\\build\\project.sharpmake.template", result);

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
		SKString filePath = ProjectPath + "\\" +  ProjectName + "\\Build\\build.sharpmake.cs";
		SKString dirPath = ProjectPath + "\\" + ProjectName;

#if defined(_WIN32) || defined(_WIN64)
		SKString path = dirPath;
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

		FileSystem::ReadFile(mainPath + "\\build\\entry.cpp.template", result);
		FileSystem::WriteFile(path + "entry.cpp", result);

		GenerateVSProject(filePath, dirPath, ProjectName, EnginePath);
		CompileProject(dirPath, ProjectName);
		CreateSKProject(dirPath, ProjectName);
	}

	void BuildTool::GenerateVSProject(SKString filePath, SKString dirPath, SKString projectName, SKString EnginePath)
	{
#if defined(_WIN32) || defined(_WIN64)
		SKString command = "cd " + EnginePath + "\\Build && dir && build_win.bat ";
		command.append(filePath);
		system(command.c_str());

		//make this the new way of reading files
		std::string path = dirPath.c_str();
		path += "\\";
		path += projectName.c_str();
		path += ".vcxproj";
		std::ifstream in(path);
		std::stringstream buffer;
		buffer << in.rdbuf();
		std::string contents(buffer.str());
		std::string sub = "<ProgramDatabaseFile>binaries\\";
		sub += projectName.c_str();
		sub += ".pdb</ProgramDatabaseFile>";

		contents.replace(contents.find(sub), sub.length(), "<ProgramDatabaseFile>binaries\\$(TargetName)-$([System.DateTime]::Now.ToString(\"HH_mm_ss_fff\")).pdb</ProgramDatabaseFile>");

		std::ofstream o(path.c_str());
		o << contents << std::endl;
#endif
	}

	void BuildTool::CompileProject(SKString path, SKString ProjectName)
	{
#if defined(_WIN32) || defined(_WIN64)
		SKString command = "cd ";
		command.append(path);
		command.append(" && msbuild.exe ");
		command.append(ProjectName);
		command.append(".vcxproj");
		system(command.c_str());
#endif
	}

	void BuildTool::CreateSKProject(SKString path, SKString ProjectName)
	{
		json j;

		j["name"] = ProjectName.c_str();
		SKString dllPath = path + "\\binaries\\" + ProjectName + ".dll";
		j["dll"] = dllPath.c_str();

		SKString file = path + "\\";
		file.append(ProjectName);
		file.append(".skproject");

		std::ofstream o(file.c_str());
		o << std::setw(4) << j << std::endl;
	}

	nlohmann::json BuildTool::ReadSKProject(SKString path)
	{
		json j;

		std::ifstream i(path.c_str());
		i >> j;

		return j;
	}

}