using System;

namespace Communication.Infrastructure
{
	/// <summary>
	/// IUDP client service.
	/// </summary>
	public interface IUDPClientService
	{
		void SendMessage(ArduinoMessage message);
		void SendMessageBytes(byte[] data);
		void SetAddress (string hostname, int port);
	}
}

