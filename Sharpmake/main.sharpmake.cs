using Sharpmake;

namespace SkelEngine
{
	[Sharpmake.Generate]
	public class  SkelEngine: Project
	{
		public string BasePath = @"[project.SharpmakeCsPath]/../Engine";

		public SkelEngine()
		{
			Name = "Skel";
			AddTargets(new Target(Platform.win64 | Platform.win32,
				DevEnv.vs2017,
				Optimization.Debug | Optimization.Release));
			SourceRootPath = "[project.BasePath]";

			IsFileNameToLower = false;
		}

		[Configure()]
		public void ConfigureAll(Configuration conf, Target target)
		{
			conf.IncludePaths.Add("[project.BasePath]");
			conf.IncludePaths.Add("[project.BasePath]/Source/Thirdparty/GLFW/include/");
			conf.IncludePaths.Add("[project.BasePath]/Source/Thirdparty/assimp/include/");
			conf.IncludePaths.Add("[project.BasePath]/Source/Thirdparty/EASTL/src/include/");
			conf.IncludePaths.Add("[project.BasePath]/Source/Thirdparty/GLEW/Source/");
			conf.IncludePaths.Add("[project.BasePath]/Source/Thirdparty/glm/Source/");
			conf.IncludePaths.Add("[project.BasePath]/Source/Thirdparty/ImGui/src/");
			conf.IncludePaths.Add("[project.BasePath]/Source/Thirdparty/Json/");

			conf.LibraryPaths.Add("[project.BasePath]/Source/Thirdparty/GLFW/lib-vc2015");
			conf.LibraryPaths.Add("[project.BasePath]/Source/Thirdparty/assimp/lib");

			conf.TargetLibraryPath = "[project.BasePath]/../Binaries/libs";
			conf.ProjectPath = "[project.SharpmakeCsPath]/../Engine";
			conf.IntermediatePath = "[project.SharpmakeCsPath]/../Binaries/Intermediate/Engine";
			conf.TargetPath = "[project.SharpmakeCsPath]/../Binaries";
			conf.Defines.Add("_CRT_SECURE_NO_WARNINGS");
			conf.Defines.Add("GLEW_STATIC");
			conf.LibraryFiles.Add("assimp.lib");
			conf.LibraryFiles.Add("glfw3.lib");
			conf.LibraryFiles.Add("opengl32.lib");
			conf.SolutionFolder = "Engine";

			conf.Options.Add(Sharpmake.Options.Vc.Linker.SubSystem.Console);

			if (target.Optimization == Optimization.Debug)
			{
				conf.Options.Add(Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDebugDLL);
				conf.Defines.Add("_EDITOR");
			}
			else
			{
				conf.Options.Add(Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDLL);
			}
			
			conf.Options.Add(Options.Vc.Compiler.Exceptions.Enable);
			conf.Options.Add(new Sharpmake.Options.Vc.Compiler.DisableSpecificWarnings("4201", "4005", "4251"));

		}
	}

	[Sharpmake.Generate]
	public class SkelEngineSolution : Sharpmake.Solution
	{
		public SkelEngineSolution()
		{
			Name = "SkelEngine";
			AddTargets(new Target(Platform.win64 | Platform.win32, DevEnv.vs2017, Optimization.Debug | Optimization.Release));

			IsFileNameToLower = false;
		}

		[Configure()]
		public void ConfigureAll(Configuration conf, Target target)
		{
			conf.SolutionFileName = "SkelEngine";
			conf.SolutionPath = @"[solution.SharpmakeCsPath]/..";
			conf.AddProject<SkelEngine>(target);
		}
	}

	internal static class main
	{
		[Sharpmake.Main]
		public static void SharpmakeMain(Sharpmake.Arguments arguments)
		{
			arguments.Generate<SkelEngineSolution>();
		}
	}
}
