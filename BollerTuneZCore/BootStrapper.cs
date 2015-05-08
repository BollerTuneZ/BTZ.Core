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
			//TinyIoCContainer.Current.Register<INetworkConfig,NetworkConfig> ();
			TinyIoCContainer.Current.Register<IMessagePacker,MessagePacker> ();
			TinyIoCContainer.Current.Register<IUDPClientService,UDPClientService> ();
			TinyIoCContainer.Current.Register<IUDPService,UDPService> ();
			TinyIoCContainer.Current.Register<IJoyStickHandler,JoyStickHandler> ();
			TinyIoCContainer.Current.Register<IBTZJoyStickController,BTZJoyStickController> ();
			TinyIoCContainer.Current.Register<JoyStickTesting> ();
			TinyIoCContainer.Current.Register<CommunicationTest> ();
			TinyIoCContainer.Current.Register<ISteeringProcessor,SteeringProcessor> ().AsSingleton();
			TinyIoCContainer.Current.Register<ISteeringConfigMessageProcessor,SteeringConfigMessageProcessor> ().AsSingleton();
			TinyIoCContainer.Current.Register<Main> ();

		}
	}
}

