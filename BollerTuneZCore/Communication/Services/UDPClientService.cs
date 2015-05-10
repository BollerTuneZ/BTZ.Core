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
		public UDPClientService ()
		{
		}

		#region IUDPClientService implementation

		public void SendMessage (string host, int port, ArduinoMessage message)
		{
			IPEndPoint RemoteEndPoint= new IPEndPoint(
				IPAddress.Parse(host), port);
			Socket server = new Socket(AddressFamily.InterNetwork,
				SocketType.Dgram, ProtocolType.Udp);
			byte[] payload = MessageToByteArray (message);
			for (int i = 0; i < payload.Length; i++) {
				Console.WriteLine (String.Format ("i:{0} ; {0}", i, Convert.ToChar (payload [i])));
			}
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

