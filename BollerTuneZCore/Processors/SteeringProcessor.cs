using System;
using Communication.Infrastructure;
using Infrastructure;
using log4net;
using System.Threading;

namespace BollerTuneZCore
{
	public class SteeringProcessor : ISteeringProcessor
	{
		readonly IUDPClientService _clientService;
		readonly static ILog s_log = LogManager.GetLogger (typeof(SteeringProcessor));
		readonly IUDPService _steeringUdpService;
		readonly IMessagePacker _messagePacker;
		object lockCommunication = new object ();
		volatile bool Calibrated = false;
		char SetupLevel = 'N';

		public SteeringProcessor (IUDPClientService _clientService, IUDPService steeringUdpService, IMessagePacker _messagePacker)
		{
			this._clientService = _clientService;
			this._steeringUdpService = steeringUdpService;
			this._messagePacker = _messagePacker;
			this._steeringUdpService.OnReveicedData += OnReceiveData;
			new Thread(() =>
				_steeringUdpService.Run (9050)).Start();
		}
		

		void OnReceiveData (object sender, EventArgs e)
		{
			DataEventArgs args = (DataEventArgs)e;
			var message = _messagePacker.PackMessage (args.Data);

			Console.WriteLine(String.Format("Got Message {0}",message.Payload));
		}

		#region ISteeringProcessor implementation
		public void SetEnabled (bool enabled)
		{
			ArduinoMessage message;
			message = new ArduinoMessage ();
			message.LengthByte = 0x03;
			message.TypeByte = (byte)Communication.Infrastructure.SteeringState.Base;
			if (enabled) {
				message.Payload = new byte[] {
					(byte)Communication.Infrastructure.SteeringState.Enabled,
					(byte)SteeringBaseBytes.Write,
					Convert.ToByte ('Y')
				};
			} else {
				message.Payload = new byte[] {
					(byte)Communication.Infrastructure.SteeringState.Enabled,
					(byte)SteeringBaseBytes.Write,
					Convert.ToByte ('N')
				};
			}
			SendMessage (message);
		}
		public void StartSetup ()
		{
			ArduinoMessage message;
			message = new ArduinoMessage ();
			message.LengthByte = 0x02;
			message.TypeByte = (byte)SteeringControlling.Base;
			message.Payload = new byte[]{ (byte)SteeringControlling.StartSetup,Convert.ToByte('L') };
			SendMessage (message);
			SetupLevel = 'L';
			s_log.Info (String.Format("Setup Level {0}",SetupLevel));
		}

		public void ChangeSetupLevel ()
		{
			if (SetupLevel == 'L') {
				ArduinoMessage message;
				message = new ArduinoMessage ();
				message.LengthByte = 0x02;
				message.TypeByte = (byte)SteeringControlling.Base;
				message.Payload = new byte[]{ (byte)SteeringControlling.ContinueSetup,Convert.ToByte ('C') };
				SendMessage (message);
				SetupLevel = 'C';
				s_log.Info (String.Format("Setup Level {0}",SetupLevel));
			} else if (SetupLevel == 'C') {
				ArduinoMessage message;
				message = new ArduinoMessage ();
				message.LengthByte = 0x02;
				message.TypeByte = (byte)SteeringControlling.Base;
				message.Payload = new byte[]{ (byte)SteeringControlling.ContinueSetup,Convert.ToByte ('F') };
				SendMessage (message);
				SetupLevel = 'N';
				s_log.Info ("Setup Fertig");
				Calibrated = true;
			}
		}

		public void Steer (int value)
		{
			if (!Calibrated) {
				return;
			}
			ArduinoMessage message;
			message = new ArduinoMessage ();
			message.LengthByte = 0x02;
			message.TypeByte = (byte)SteeringControlling.Base;
			message.Payload = new byte[]{ (byte)SteeringControlling.Turn,Convert.ToByte(value) };
			SendMessage (message);
		}

		public void Initialize ()
		{
			s_log.Info (String.Format ("Initialize Steering {0}", DateTime.Now));
			ArduinoMessage message;
			message = new ArduinoMessage ();
			message.LengthByte = 0x03;
			message.TypeByte = (byte)SteeringConfigs.Base;
			message.Payload = new byte[]{ (byte)SteeringConfigs.InputType, (byte)SteeringBaseBytes.Write, Convert.ToByte ('R') };
			SendMessage (message);
			s_log.Info ("Set InputType to Remote");
		}

		#endregion

		void SendMessage(ArduinoMessage message)
		{
			
				_clientService.SendMessage (
					message);
		}

		//ArduinoMessage CreateControllingMessage(
	}
}

