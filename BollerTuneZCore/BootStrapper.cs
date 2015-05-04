using System;
using TinyIoC;
using Communication.Infrastructure;
using Communication;
using Infrastructure;
using JoystickApi;
using Testing;


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
			TinyIoCContainer.Current.Register<IJoyStickHandler,JoyStickHandler> ();
			TinyIoCContainer.Current.Register<IBTZJoyStickController,BTZJoyStickController> ();
			TinyIoCContainer.Current.Register<JoyStickTesting> ();

		}
	}
}

