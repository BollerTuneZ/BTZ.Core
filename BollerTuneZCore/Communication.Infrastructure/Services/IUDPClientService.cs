using System;

namespace Communication.Infrastructure
{
	/// <summary>
	/// IUDP client service.
	/// </summary>
	public interface IUDPClientService
	{
		void SendMessage(string host,int port,ArduinoMessage message);
		void SendMessageBytes(string host,int port,byte[] data);
	}
}

