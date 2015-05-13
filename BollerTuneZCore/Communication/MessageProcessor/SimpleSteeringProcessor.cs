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
		bool startSteering = false;
		int currentPosition = 0;
		System.Timers.Timer steeringTimer = new System.Timers.Timer ();

		public SimpleSteeringProcessor (IUDPClientService _clientService)
		{
			this._clientService = _clientService;
			steeringTimer.Interval = 50;
			steeringTimer.Elapsed += SteeringTimer_Elapsed;
		}

		void SteeringTimer_Elapsed (object sender, System.Timers.ElapsedEventArgs e)
		{
			_clientService.SendMessageBytes (ConnectionInfo.ArduinoHostNameSteering, ConnectionInfo.ArduinoPortSteering,
				new byte[]{ CommandByte, Convert.ToByte ('T'), Convert.ToByte (currentPosition) });
		}
		

		#region ISteeringProcessor implementation

		public void Steer (int value)
		{
			if (!startSteering) {
			
				return;
			}
			currentPosition = value;
		}

		public void SetEnabled (bool enabled)
		{
			startSteering = enabled;
			if (startSteering == true) {
				steeringTimer.Start ();
			} else {
				steeringTimer.Stop ();
			}
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
		[Obsolete]
		public void ChangeSetupLevel ()
		{
			

		}

		#endregion

		void RaiseSetup()
		{
			if (SetupState == 'N') {
				SetupState = 'Y';
			} else if (SetupState == 'Y') {
				SetupState = 'X';
			} else if (SetupState == 'X') {
				SetupState = 'C';
			} else if (SetupState == 'C') {
				SetupState = 'S';
			}
		}
	}
}

