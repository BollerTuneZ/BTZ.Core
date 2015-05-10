using System;
using Communication.Infrastructure;
using System.Net.Sockets;
using System.Net;

namespace Communication
{
	public class UDPService : IUDPService
	{
		public UDPService ()
		{
		}

		#region IUDPService implementation


		public event EventHandler OnReveicedData;
		public void Run (int port)
		{
			UdpClient udpServer = new UdpClient(port);

			while (true)
			{
				var remoteEP = new IPEndPoint(IPAddress.Any, port); 
				var data = udpServer.Receive(ref remoteEP); // listen on port 11000
				OnReveicedData(this,new DataEventArgs(){Data = data});
			}
		}
		#endregion
	}
}

