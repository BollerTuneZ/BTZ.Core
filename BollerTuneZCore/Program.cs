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

			//JoyStickTesting testing = TinyIoC.TinyIoCContainer.Current.Resolve<JoyStickTesting> ();
			CommunicationTest testing = new CommunicationTest();
			testing.RunTests ();
			//testing.Run ();
			/*
			Console.WriteLine ("Hello World!");
			new Thread (() => {
				Testing testing = new Testing();
				testing.Run();
			});
*/
			Console.ReadKey ();
		}
	}
}
