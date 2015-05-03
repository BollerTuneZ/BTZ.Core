using System;
using TinyIoC;
using Communication.Infrastructure;
using Communication;


namespace BollerTuneZCore
{
	public static class BootStrapper
	{
		static BootStrapper ()
		{
		}
		public static void Run()
		{
			TinyIoCContainer.Current.Register<IUDPClientService,UDPClientService> ();
		}
	}
}

