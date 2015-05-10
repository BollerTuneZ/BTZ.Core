using System;
using Communication.Infrastructure;
using Infrastructure;

namespace Communication
{
	public class EngineProcessor : IEngineProcessor
	{
		ArduinoMessage _engineSpeedMessage;

		readonly IUDPClientService _client;

		public EngineProcessor (IUDPClientService _client)
		{
			this._client = _client;
			_engineSpeedMessage = new ArduinoMessage {
				LengthByte = 0x02,
				TypeByte = Convert.ToByte('D'),
			};
		}
		

		#region IEngineProcessor implementation

		public void Drive (int value)
		{
			char dir = 'F';
			if (value < 0) {
				dir = 'B';
				value = value * (-1);
			}

			_engineSpeedMessage.Payload = new byte[]{ Convert.ToByte(dir),Convert.ToByte(value)};

			_client.SendMessage (ConnectionInfo.ArduinoHostNameEngine, ConnectionInfo.ArduinoPortEngine
				, _engineSpeedMessage);
			Console.WriteLine (_engineSpeedMessage.ToString ());
		}

		#endregion
	}
}

