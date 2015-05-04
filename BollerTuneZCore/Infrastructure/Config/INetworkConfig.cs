using System;

namespace Infrastructure
{
	/// <summary>
	/// Hält und verwaltet die Configs fürs netzwerk
	/// </summary>
	public interface INetworkConfig
	{
		void SetSteeringConnectionInfos(string hostname,int port);

		void SetPowerConnectionInfos(string hostname,int port);

		ConnectionInfo GetSteeringConnectionInfo();
		ConnectionInfo GetPowerConnectionInfo();
	}
}

