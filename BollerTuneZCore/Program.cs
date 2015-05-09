using System;
using System.Threading;
using Testing;
using Communication.Infrastructure;
using Infrastructure;
using log4net.Repository.Hierarchy;
using log4net.Layout;
using log4net.Appender;
using log4net;
using log4net.Core;


namespace BollerTuneZCore
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			Setup ();
			BootStrapper.Run ();
			/*
			ISteeringProcessor steeringProcessor = TinyIoC.TinyIoCContainer.Current.Resolve<ISteeringProcessor> ();
			ISteeringConfigMessageProcessor steeringConfigMessageProcessor = TinyIoC.TinyIoCContainer.Current.Resolve<ISteeringConfigMessageProcessor> ();
			IBTZJoyStickController _joyStick = TinyIoC.TinyIoCContainer.Current.Resolve<IBTZJoyStickController> ();*/
			Main programm = TinyIoC.TinyIoCContainer.Current.Resolve<BollerTuneZCore.Main> ();
			Console.WriteLine ("Going to run");
			programm.Run ();
			//CommunicationTest testing = new CommunicationTest();
			//testing.RunTests ();
			Console.ReadKey ();
			/*
			JoyStickTesting testing = TinyIoC.TinyIoCContainer.Current.Resolve<JoyStickTesting> ();

			/*
			Console.WriteLine ("Hello World!");
			new Thread (() => {
				Testing testing = new Testing();
				testing.Run();
			});
*/
		}
		public static void Setup()
		{
			Hierarchy hierarchy = (Hierarchy)LogManager.GetRepository();

			PatternLayout patternLayout = new PatternLayout();
			patternLayout.ConversionPattern = "%date [%thread] %-5level %logger - %message%newline";
			patternLayout.ActivateOptions();

			RollingFileAppender roller = new RollingFileAppender();
			roller.AppendToFile = false;
			roller.File = @"Logs\EventLog.txt";
			roller.Layout = patternLayout;
			roller.MaxSizeRollBackups = 5;
			roller.MaximumFileSize = "1GB";
			roller.RollingStyle = RollingFileAppender.RollingMode.Size;
			roller.StaticLogFileName = true;            
			roller.ActivateOptions();
			hierarchy.Root.AddAppender(roller);

			MemoryAppender memory = new MemoryAppender();
			memory.ActivateOptions();
			hierarchy.Root.AddAppender(memory);

			ConsoleAppender consoleAppender = new ConsoleAppender {
				Layout = patternLayout,
			};
			consoleAppender.ActivateOptions ();
			hierarchy.Root.AddAppender (consoleAppender);

			hierarchy.Root.Level = Level.Info;
			hierarchy.Configured = true;
		}

	}
}
