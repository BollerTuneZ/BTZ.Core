using System;
using Communication.Infrastructure;
using System.Net;
using System.Net.Sockets;


namespace Communication
{
	public class UDPClientService : IUDPClientService
	{
		const byte StartByte = 0x01;
		const byte EndByte = 0xDE;
		string hostAddress = "";
		int hostPort = 0;
		private IPEndPoint RemoteEndPoint;
		Socket server;
		public UDPClientService ()
		{
		}

		#region IUDPClientService implementation

		public void SetAddress (string hostname, int port)
		{
			RemoteEndPoint= new IPEndPoint(
				IPAddress.Parse(hostname), port);
			server = new Socket(AddressFamily.InterNetwork,
				SocketType.Dgram, ProtocolType.Udp);
		}

		public void SendMessageBytes ( byte[] data)
		{
			byte[] payload = data;
			server.SendTo(payload, payload.Length, SocketFlags.None, RemoteEndPoint);
		}

		public void SendMessage (ArduinoMessage message)
		{
			byte[] payload = MessageToByteArray (message);

			server.SendTo(payload, payload.Length, SocketFlags.None, RemoteEndPoint);
		}
		#endregion


		byte[] MessageToByteArray(ArduinoMessage message)
		{
			int totalLength = message.Payload.Length + 4;

			byte[] payload = new byte[totalLength];
			payload [0] = StartByte;
			payload [1] = message.TypeByte;
			payload [2] = message.LengthByte;

			for (int i = 0; i < message.Payload.Length; i++) {
				payload [i + 3] = message.Payload [i];
			}
			payload [totalLength - 1] = EndByte;

			return payload;
		}
	}
}

