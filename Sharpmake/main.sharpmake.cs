using Sharpmake;

namespace SkelEngine
{
	[Sharpmake.Generate]
	public class SkelEngine : Project
	{
		public string BasePath = @"[project.SharpmakeCsPath]/../Engine";

		public SkelEngine()
		{
			Name = "Engine";

			AddTargets(new Target(
				Platform.win64 | Platform.win32,
				DevEnv.vs2017,
				Optimization.Debug | Optimization.Release,
				OutputType.Dll | OutputType.Lib
			));

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

			conf.LibraryPaths.Add("[project.BasePath]/Source/Thirdparty/GLFW/lib-vc2015");
			conf.LibraryPaths.Add("[project.BasePath]/Source/Thirdparty/assimp/lib");

			conf.TargetLibraryPath = "[project.BasePath]/../bin/libs";
			conf.ProjectPath = "[project.SharpmakeCsPath]/../Engine";
			conf.IntermediatePath = "[project.SharpmakeCsPath]/../bin/Intermediate/Engine";
			conf.TargetPath = "[project.SharpmakeCsPath]/../bin";
			conf.Defines.Add("_CRT_SECURE_NO_WARNINGS");
			conf.Defines.Add("GLEW_STATIC");
			conf.LibraryFiles.Add("assimp.lib");
			conf.LibraryFiles.Add("glfw3.lib");
			conf.LibraryFiles.Add("opengl32.lib");
			conf.SolutionFolder = "Engine";

			// The library wants LIBRARY_COMPILE defined when it compiles the
			// library, so that it knows whether it must use dllexport or
			// dllimport.
			conf.Defines.Add("SKEL_COMPILE");

			if (target.OutputType == OutputType.Dll)
			{
				// We want this to output a shared library. (DLL)
				conf.Output = Configuration.OutputType.Dll;

				// This library project expects LIBRARY_DLL symbol to be defined
				// when used as a DLL. While we could define it in the executable,
				// it is better to put it as an exported define. That way, any
				// projects with a dependency on this one will have LIBRARY_DLL
				// automatically defined by Sharpmake.
				conf.ExportDefines.Add("SKEL_DLL");

				// Exported defines are not necessarily defines as well, so we need
				// to add LIBRARY_DLL as an ordinary define too.
				conf.Defines.Add("SKEL_DLL");
			}
			else if (target.OutputType == OutputType.Lib)
			{
				// We want this to output a static library. (LIB)
				conf.Output = Configuration.OutputType.Lib;
			}

			if (target.Optimization == Optimization.Debug)
				conf.Options.Add(Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDebugDLL);
			else
				conf.Options.Add(Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDLL);

			conf.Options.Add(Options.Vc.Compiler.Exceptions.Enable);
			conf.Options.Add(new Sharpmake.Options.Vc.Compiler.DisableSpecificWarnings("4201", "4005", "4251"));
		}
	}

	[Sharpmake.Generate]
	public class SkelEditor : Project
	{
		public SkelEditor()
		{
			Name = "Editor";
			AddTargets(new Target(Platform.win64 | Platform.win32,
				DevEnv.vs2017,
				Optimization.Debug | Optimization.Release));
			SourceRootPath = "[project.SharpmakeCsPath]/../Editor";

			IsFileNameToLower = false;
		}

		[Configure()]
		public void ConfigureAll(Configuration conf, Target target)
		{
			conf.ProjectFileName = "Editor";
			conf.ProjectPath = @"[project.SharpmakeCsPath]/../Editor";
			conf.IntermediatePath = "[project.SharpmakeCsPath]/../bin/Editor";
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.Exceptions.Enable);
			conf.TargetPath = "[project.SharpmakeCsPath]/../bin";
			conf.Defines.Add("_CRT_SECURE_NO_WARNINGS");
			conf.SolutionFolder = "Engine";
			conf.Defines.Add("GLEW_STATIC");

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
			
			conf.Options.Add(new Sharpmake.Options.Vc.Compiler.DisableSpecificWarnings("4201", "4251"));

			conf.AddPrivateDependency<SkelEngine>(target);
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
			conf.AddProject<SkelEditor>(target);
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
