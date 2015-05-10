using System;
using Communication.Infrastructure;
using Infrastructure;

namespace Communication
{
	public class SimpleSteeringProcessor : ISteeringProcessor
	{
		char SetupState = 'N';
		const byte CommandByte = 0x63;
		IUDPClientService _clientService;

		public SimpleSteeringProcessor (IUDPClientService _clientService)
		{
			this._clientService = _clientService;
		}
		

		#region ISteeringProcessor implementation

		public void Steer (int value)
		{
			if (value > 0 && value < 256) {
				_clientService.SendMessageBytes(ConnectionInfo.ArduinoHostNameSteering,ConnectionInfo.ArduinoPortSteering,
					new byte[]{CommandByte,};
			}
			throw new NotImplementedException ();
		}

		public void SetEnabled (bool enabled)
		{
			throw new NotImplementedException ();
		}

		public void Initialize ()
		{
			throw new NotImplementedException ();
		}

		public void StartSetup ()
		{
			throw new NotImplementedException ();
		}

		public void ChangeSetupLevel ()
		{
			throw new NotImplementedException ();
		}

		#endregion
	}
}

