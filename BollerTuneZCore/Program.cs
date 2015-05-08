using System;
using System.Threading;
using Testing;
namespace BollerTuneZCore
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			BootStrapper.Run ();

			var programm = TinyIoC.TinyIoCContainer.Current.Resolve<Main> ();
			programm.Run ();
			Console.ReadKey ();
			/*
			JoyStickTesting testing = TinyIoC.TinyIoCContainer.Current.Resolve<JoyStickTesting> ();
			//CommunicationTest testing = new CommunicationTest();
			//testing.RunTests ();
			testing.Run ();
			/*
			Console.WriteLine ("Hello World!");
			new Thread (() => {
				Testing testing = new Testing();
				testing.Run();
			});
*/
		}
	}
}
