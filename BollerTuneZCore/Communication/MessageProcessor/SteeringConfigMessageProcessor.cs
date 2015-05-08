using System;
using Communication.Infrastructure;
using Infrastructure;


namespace Communication
{
	public class SteeringConfigMessageProcessor : ISteeringConfigMessageProcessor
	{
		IUDPClientService _client;

		public SteeringConfigMessageProcessor (IUDPClientService _client)
		{
			this._client = _client;
		}
		

		#region ISteeringConfigMessageProcessor implementation

		public void WriteConfigs ()
		{
			throw new NotImplementedException ();
		}

		public void ReadConfigs ()
		{
			foreach (SteeringConfigs config in Enum.GetValues(typeof(SteeringConfigs)))
			{
				if (config == SteeringConfigs.Non || config == SteeringConfigs.Base) {
					continue;
				}
				var message = CreateReadMessage (config);
				_client.SendMessage (ConnectionInfo.ArduinoHostNameSteering, ConnectionInfo.ArduinoPortSteering, message);
			}
		}
		#endregion

		ArduinoMessage CreateReadMessage(SteeringConfigs config)
		{
			ArduinoMessage message = new ArduinoMessage {
				LengthByte = 0x02,
				TypeByte = SteeringConfigs.Base,
				Payload = new byte[]{(byte)config,(byte)SteeringBaseBytes.Read}
			};
			return message;
		}
	}
}

