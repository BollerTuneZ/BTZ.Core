using System;
using System.Threading;
using Testing;
using Communication.Infrastructure;
using Infrastructure;


namespace BollerTuneZCore
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			BootStrapper.Run ();
			ISteeringProcessor steeringProcessor = TinyIoC.TinyIoCContainer.Current.Resolve<ISteeringProcessor> ();
			ISteeringConfigMessageProcessor steeringConfigMessageProcessor = TinyIoC.TinyIoCContainer.Current.Resolve<ISteeringConfigMessageProcessor> ();
			IBTZJoyStickController _joyStick = TinyIoC.TinyIoCContainer.Current.Resolve<IBTZJoyStickController> ();
			Main programm = new BollerTuneZCore.Main (steeringProcessor, steeringConfigMessageProcessor, _joyStick);
			Console.WriteLine ("Going to run");
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
