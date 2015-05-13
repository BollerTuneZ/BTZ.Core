using System;
using Communication.Infrastructure;
using System.Threading;

namespace BollerTuneZCore
{
	public class Testing
	{
		IUDPClientService _udpClientService;

		public Testing ()
		{
			_udpClientService = TinyIoC.TinyIoCContainer.Current.Resolve<IUDPClientService> ();
		}
		

		public void Run()
		{
			ArduinoMessage message;
			string host = "192.168.2.177";
			int port = 8888;

			message = new ArduinoMessage ();
			message.LengthByte = 0x01;
			message.TypeByte = 0x02;
			message.Payload = new byte[]{0x1F};
			_udpClientService.SendMessage ( message);
		}
	}
}

