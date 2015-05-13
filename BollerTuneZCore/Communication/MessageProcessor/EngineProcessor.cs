using System;
using Communication.Infrastructure;
using Infrastructure;
using System.Timers;
namespace Communication
{
	public class EngineProcessor : IEngineProcessor
	{
		ArduinoMessage _engineSpeedMessage;
		System.Timers.Timer engineSpeedTimer = new Timer();
		readonly IUDPClientService _client;
		DateTime lastTimeChanged = DateTime.Now;
		int EngineSpeed = 0;

		public EngineProcessor (IUDPClientService _client)
		{
			this._client = _client;
			_engineSpeedMessage = new ArduinoMessage {
				LengthByte = 0x02,
				TypeByte = Convert.ToByte('D'),
			};
			engineSpeedTimer.Interval = 50;
			engineSpeedTimer.Elapsed += OnEngineSpeedElapsed;
			engineSpeedTimer.Start ();
		}

		void OnEngineSpeedElapsed (object sender, ElapsedEventArgs e)
		{
			_client.SendMessage (ConnectionInfo.ArduinoHostNameEngine, ConnectionInfo.ArduinoPortEngine
				, _engineSpeedMessage);
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

		}

		#endregion
	}
}

