using Sharpmake;

namespace SkelEngine
{
	[Sharpmake.Generate]
	public class EASTL : Project
	{
		public string BasePath = @"[project.SharpmakeCsPath]/../ThirdParty/EASTL";

		public EASTL()
		{
			Name = "EASTL";

			AddTargets(new Target(
				Platform.win64 | Platform.win32 ,
				DevEnv.vs2017,
				Optimization.Debug | Optimization.Release,
				OutputType.Lib
			));

			SourceRootPath = "[project.BasePath]";

			IsFileNameToLower = false;
		}

		[Configure()]
		public void Configure(Configuration conf, Target target)
		{
			conf.Output = Project.Configuration.OutputType.Lib;
			conf.IncludePaths.Add("[project.BasePath]/src/include");
			conf.TargetLibraryPath = "[project.BasePath]/../EASTL/libs";
			conf.ProjectPath = "[project.SharpmakeCsPath]/../ThirdParty/EASTL";
			conf.IntermediatePath = "[project.SharpmakeCsPath]/../bin/EASTL";
			conf.Defines.Add("_CRT_SECURE_NO_WARNINGS");
			conf.SolutionFolder = "ThirdParty";
		}
	}

	[Sharpmake.Generate]
	public class ImGUI : Project
	{
		public string BasePath = @"[project.SharpmakeCsPath]/../ThirdParty/ImGUI";

		public ImGUI()
		{
			Name = "ImGUI";

			AddTargets(new Target(
				Platform.win64 | Platform.win32,
				DevEnv.vs2017,
				Optimization.Debug | Optimization.Release,
				OutputType.Lib
			));

			SourceRootPath = "[project.BasePath]/src";

			IsFileNameToLower = false;
		}

		[Configure()]
		public void Configure(Configuration conf, Target target)
		{
			conf.Output = Project.Configuration.OutputType.Lib;
			conf.IncludePaths.Add("[project.BasePath]/src");
			conf.TargetLibraryPath = "[project.BasePath]/../ImGUI/libs";
			conf.ProjectPath = "[project.SharpmakeCsPath]/../ThirdParty/ImGUI";
			conf.IntermediatePath = "[project.SharpmakeCsPath]/../bin/ImGUI";
			conf.SolutionFolder = "ThirdParty";
		}
	}

    [Sharpmake.Generate]
	public class GLEW : Project
	{
		public string BasePath = @"[project.SharpmakeCsPath]/../ThirdParty/GLEW";

		public GLEW()
		{
			Name = "GLEW";

			AddTargets(new Target(
				Platform.win64 | Platform.win32,
				DevEnv.vs2017,
				Optimization.Debug | Optimization.Release,
				OutputType.Lib
			));

			SourceRootPath = "[project.BasePath]/Source";

			IsFileNameToLower = false;
		}

		[Configure()]
		public void Configure(Configuration conf, Target target)
		{
			conf.Output = Project.Configuration.OutputType.Lib;
			conf.IncludePaths.Add("[project.BasePath]/Source");
			conf.Defines.Add("GLEW_STATIC");
			conf.TargetLibraryPath = "[project.BasePath]/../GLEW/libs";
			conf.ProjectPath = "[project.SharpmakeCsPath]/../ThirdParty/GLEW";
			conf.IntermediatePath = "[project.SharpmakeCsPath]/../bin/GLEW";
			conf.SolutionFolder = "ThirdParty";
		}
	}

    
    [Sharpmake.Generate]
	public class GLM : Project
	{
		public string BasePath = @"[project.SharpmakeCsPath]/../ThirdParty/GLM";

		public GLM()
		{
			Name = "GLM";

			AddTargets(new Target(
				Platform.win64 | Platform.win32,
				DevEnv.vs2017,
				Optimization.Debug | Optimization.Release,
				OutputType.Lib
			));

			SourceRootPath = "[project.BasePath]/Source";

			IsFileNameToLower = false;
		}

		[Configure()]
		public void Configure(Configuration conf, Target target)
		{
			conf.Output = Project.Configuration.OutputType.Lib;
			conf.IncludePaths.Add("[project.BasePath]/Source");
			conf.TargetLibraryPath = "[project.BasePath]/../GLM/libs";
			conf.ProjectPath = "[project.SharpmakeCsPath]/../ThirdParty/GLM";
			conf.IntermediatePath = "[project.SharpmakeCsPath]/../bin/GLM";
			conf.SolutionFolder = "ThirdParty";
		}
	}

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
				OutputType.Lib
			));

			SourceRootPath = "[project.BasePath]";

			IsFileNameToLower = false;
		}

		[Configure()]
		public void Configure(Configuration conf, Target target)
		{
			conf.Output = Project.Configuration.OutputType.Lib;
			conf.IncludePaths.Add("[project.BasePath]");
            conf.IncludePaths.Add("[project.BasePath]/../Thirdparty/GLFW/include");
            conf.IncludePaths.Add("[project.BasePath]/../Thirdparty/assimp/include");
			conf.TargetLibraryPath = "[project.BasePath]/../ThirdParty/Engine/libs";
			conf.ProjectPath = "[project.SharpmakeCsPath]/../Engine";
			conf.IntermediatePath = "[project.SharpmakeCsPath]/../bin/Engine";
			conf.Defines.Add("_CRT_SECURE_NO_WARNINGS");
            conf.Defines.Add("GLEW_STATIC");
			conf.SolutionFolder = "Engine";

			conf.AddPublicDependency<EASTL>(target);
			conf.AddPublicDependency<ImGUI>(target);
            conf.AddPublicDependency<GLEW>(target);
            conf.AddPublicDependency<GLM>(target);
		}
	}

	[Sharpmake.Generate]
	public class SkelEngineSandbox : Project
	{
		public SkelEngineSandbox()
		{
			Name = "Sandbox";
			AddTargets(new Target(Platform.win64 | Platform.win32,
				DevEnv.vs2017,
				Optimization.Debug | Optimization.Release));
			SourceRootPath = "[project.SharpmakeCsPath]/../Sandbox";

			IsFileNameToLower = false;
		}

		[Configure()]
		public void ConfigureAll(Configuration conf, Target target)
		{
			conf.ProjectFileName = "Sandbox";
			conf.ProjectPath = @"[project.SharpmakeCsPath]/../Sandbox";
			conf.IntermediatePath = "[project.SharpmakeCsPath]/../bin/Sandbox";
            conf.LibraryPaths.Add("[project.SharpmakeCsPath]/../Thirdparty/GLFW/lib-vc2015");
            conf.LibraryPaths.Add("[project.SharpmakeCsPath]/../Thirdparty/assimp/lib");
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.Exceptions.Enable);
			conf.Defines.Add("_CRT_SECURE_NO_WARNINGS");
            conf.Defines.Add("GLEW_STATIC");
            conf.LibraryFiles.Add("assimp.lib");
            conf.LibraryFiles.Add("glfw3.lib");
			conf.LibraryFiles.Add("opengl32.lib");
			
			conf.Options.Add(Sharpmake.Options.Vc.Linker.SubSystem.Console);

			if (target.Optimization == Optimization.Debug)
				conf.Defines.Add("_EDITOR");


            conf.AddPublicDependency<GLEW>(target);
			conf.AddPublicDependency<SkelEngine>(target);
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
			conf.AddProject<SkelEngineSandbox>(target);
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
