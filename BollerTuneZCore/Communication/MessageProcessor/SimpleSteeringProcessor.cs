using System;
using Communication.Infrastructure;
using Infrastructure;
using log4net;

namespace Communication
{
	public class SimpleSteeringProcessor : ISteeringProcessor
	{
		char SetupState = 'N';
		const byte CommandByte = 0x63;
		IUDPClientService _clientService;
		ILog log = LogManager.GetLogger(typeof(SimpleSteeringProcessor));
		char Isenabled = 'N';
		public SimpleSteeringProcessor (IUDPClientService _clientService)
		{
			this._clientService = _clientService;
		}
		

		#region ISteeringProcessor implementation

		public void Steer (int value)
		{
			if (value > 0 && value < 256) {
				_clientService.SendMessageBytes (ConnectionInfo.ArduinoHostNameSteering, ConnectionInfo.ArduinoPortSteering,
					new byte[]{ CommandByte, Convert.ToByte ('T'), Convert.ToByte (value) });
			}
			log.Info(String.Format("Position: {0}",value));
		}

		public void SetEnabled (bool enabled)
		{
			if (Isenabled == 'R') {
				Isenabled = 'N';
			} else {
				Isenabled = 'R';
			}
			_clientService.SendMessageBytes (ConnectionInfo.ArduinoHostNameSteering, ConnectionInfo.ArduinoPortSteering,
				new byte[]{ CommandByte, Convert.ToByte ('S'), Convert.ToByte (Isenabled) });
			log.Info(String.Format("Enabled: {0}",Isenabled));
		}

		public void Initialize ()
		{
			_clientService.SendMessageBytes (ConnectionInfo.ArduinoHostNameSteering, ConnectionInfo.ArduinoPortSteering,
				new byte[]{ CommandByte, Convert.ToByte ('I'), Convert.ToByte ('R') });
			log.Info("Initialized Steering");
					
		}

		public void StartSetup ()
		{
			if (SetupState == 'S') {
				SetupState = 'N';
			}
		}

		public void ChangeSetupLevel ()
		{
			if (SetupState == 'S') {
				_clientService.SendMessageBytes (ConnectionInfo.ArduinoHostNameSteering, ConnectionInfo.ArduinoPortSteering,
					new byte[]{ CommandByte, Convert.ToByte ('S'), Convert.ToByte (SetupState) });
			}
			log.Info(String.Format("Change SetupState to: {0}",SetupState));

		}

		#endregion

		void RaiseSetup()
		{
			if (SetupState == 'N') {
				SetupState = 'Y';
			} else if (SetupState == 'Y') {
				SetupState = 'X';
			} else if (SetupState == 'X') {
				SetupState = 'S';
			}
		}
	}
}

