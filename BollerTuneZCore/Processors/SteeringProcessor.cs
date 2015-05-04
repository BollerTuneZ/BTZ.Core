using System;
using Communication.Infrastructure;
using Infrastructure;

namespace BollerTuneZCore
{
	public class SteeringProcessor : ISteeringProcessor
	{
		readonly IUDPClientService _clientService;
		readonly INetworkConfig _networkconfig;

		public SteeringProcessor (IUDPClientService _clientService, INetworkConfig _networkconfig)
		{
			this._clientService = _clientService;
			this._networkconfig = _networkconfig;
		}
		

		#region ISteeringProcessor implementation

		public void Steer (int value)
		{
			ArduinoMessage message;
			message = new ArduinoMessage ();
			message.LengthByte = 0x01;
			message.TypeByte = EnumConverter.MessageTypeToType (MessageType.Steering_position);
			message.Payload = new byte[]{ Convert.ToByte (value) };
			_clientService.SendMessage (_networkconfig.GetSteeringConnectionInfo().Hostname,
				_networkconfig.GetSteeringConnectionInfo().Port,
				message);
		}

		public void Initialize ()
		{
			
		}

		#endregion
	}
}

