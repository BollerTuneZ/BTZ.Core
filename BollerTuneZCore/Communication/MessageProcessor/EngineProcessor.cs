using System;
using Communication.Infrastructure;
using Infrastructure;

namespace Communication
{
	public class EngineProcessor : IEngineProcessor
	{
		ArduinoMessage _engineSpeedMessage;

		readonly IUDPClientService _client;
		DateTime lastTimeChanged = DateTime.Now;
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

			var diff = DateTime.Now.Subtract (lastTimeChanged);
			if (diff.Milliseconds > 50 || value == 0) {
				_client.SendMessage (ConnectionInfo.ArduinoHostNameEngine, ConnectionInfo.ArduinoPortEngine
					, _engineSpeedMessage);
				lastTimeChanged = DateTime.Now;
			}


			Console.WriteLine (_engineSpeedMessage.ToString ());
		}

		#endregion
	}
}

