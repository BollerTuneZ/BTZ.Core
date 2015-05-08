using System;
using Infrastructure;

namespace BollerTuneZCore
{
	public class NetworkConfig : INetworkConfig
	{
		public NetworkConfig ()
		{
			SteeringConnectionInfo = new ConnectionInfo () {
				Hostname = "192.168.1.117",
				Port = 8888
			};

			PowerConnectionInfo = new ConnectionInfo () {
				Hostname = "192.168.1.118",
				Port = 8888
			};
		}

		#region INetworkConfig implementation

		public ConnectionInfo GetSteeringConnectionInfo ()
		{
			return SteeringConnectionInfo;
		}

		public ConnectionInfo GetPowerConnectionInfo ()
		{
			return PowerConnectionInfo;
		}

		public void SetSteeringConnectionInfos (string hostname, int port)
		{
			SteeringConnectionInfo.Hostname = hostname;
			SteeringConnectionInfo.Port = port;
		}

		public void SetPowerConnectionInfos (string hostname, int port)
		{
			PowerConnectionInfo.Hostname = hostname;
			PowerConnectionInfo.Port = port;
		}

		#endregion
		public ConnectionInfo SteeringConnectionInfo{get;set;}
		public ConnectionInfo PowerConnectionInfo{get;set;}

	}
}

