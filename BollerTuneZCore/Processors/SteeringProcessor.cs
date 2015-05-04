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
		readonly INetworkConfig _networkconfig;
		readonly static ILog s_log = LogManager.GetLogger (typeof(SteeringProcessor));
		readonly IUDPService _steeringUdpService;
		readonly IMessagePacker _messagePacker;
		volatile bool Calibrated = false;

		public SteeringProcessor (IUDPClientService _clientService, INetworkConfig _networkconfig, IUDPService _steeringUdpService, IMessagePacker _messagePacker)
		{
			this._clientService = _clientService;
			this._networkconfig = _networkconfig;
			this._steeringUdpService = _steeringUdpService;
			this._messagePacker = _messagePacker;
			this._steeringUdpService.OnReveicedData += OnReceiveData;
			this._steeringUdpService.Run (9050);
		}
		

		void OnReceiveData (object sender, EventArgs e)
		{
			DataEventArgs args = (DataEventArgs)e;
			var message = _messagePacker.PackMessage (args.Data);

			if (message.TypeByte == 0x18) {
				Calibrated = true;
			}
		}

		#region ISteeringProcessor implementation

		public void Steer (int value)
		{
			if (!Calibrated) {
				return;
			}
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
			s_log.Info (String.Format ("Initialize Steering {0}", DateTime.Now));
			ArduinoMessage message;
			message = new ArduinoMessage ();
			message.LengthByte = 0x01;
			message.TypeByte = 0x03;
			message.Payload = new byte[]{ 0x02 };
			_clientService.SendMessage (_networkconfig.GetSteeringConnectionInfo().Hostname,
				_networkconfig.GetSteeringConnectionInfo().Port,
				message);
			s_log.Info (String.Format ("Send Command for calibrating {0}", DateTime.Now));
			new Thread (() => {
				while (!Calibrated) {
					s_log.Info ("waiting for complete Calibrate");
					Thread.Sleep (1000);
				}
			}).Start ();

		}

		#endregion
	}
}

