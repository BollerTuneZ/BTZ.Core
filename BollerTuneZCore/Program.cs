using System;
using System.Threading;

namespace BollerTuneZCore
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			BootStrapper.Run ();
			Console.WriteLine ("Hello World!");
			new Thread (() => {
				Testing testing = new Testing();
				testing.Run();
			}).Start ();

			Console.ReadKey ();
		}
	}
}
