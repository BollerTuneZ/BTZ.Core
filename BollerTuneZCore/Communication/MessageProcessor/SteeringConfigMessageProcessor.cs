using System;
using Communication.Infrastructure;
using Infrastructure;
using System.Threading;


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
			foreach (SteeringConfigs config in Enum.GetValues(typeof(SteeringConfigs)))
			{
				if (config == SteeringConfigs.Non || config == SteeringConfigs.Base) {
					continue;
				}
				ArduinoMessage message = null;
				switch (config) {
				case SteeringConfigs.Center:
					message = CreateWriteMessage (config,Convert.ToByte( SteeringConfigCollection.Center));
					break;
				case SteeringConfigs.DirLeft:
					message = CreateWriteMessage (config,Convert.ToByte( SteeringConfigCollection.DirLeft));
					break;
				case SteeringConfigs.DirRight:
					message = CreateWriteMessage (config,Convert.ToByte( SteeringConfigCollection.DirRight));
					break;
				case SteeringConfigs.InputType:
					message = CreateWriteMessage (config,Convert.ToByte( SteeringConfigCollection.InputType));
					break;
				case SteeringConfigs.InvertDirection:
					message = CreateWriteMessage (config,Convert.ToByte( SteeringConfigCollection.InvertDirection));
					break;
				case SteeringConfigs.LeftOff:
					message = CreateWriteMessage (config,Convert.ToByte( SteeringConfigCollection.LeftOff));
					break;
				case SteeringConfigs.LeftOn:
					message = CreateWriteMessage (config,Convert.ToByte( SteeringConfigCollection.LeftOn));
					break;
				case SteeringConfigs.MaximalSpeed:
					message = CreateWriteMessage (config,Convert.ToByte( SteeringConfigCollection.MaxSpeed));
					break;
				case SteeringConfigs.MinimalSpeed:
					message = CreateWriteMessage (config,Convert.ToByte( SteeringConfigCollection.MinSpeed));
					break;
				case SteeringConfigs.RightOff:
					message = CreateWriteMessage (config,Convert.ToByte( SteeringConfigCollection.RightOff));
					break;
				case SteeringConfigs.RightOn:
					message = CreateWriteMessage (config,Convert.ToByte( SteeringConfigCollection.RightOn));
					break;
				case SteeringConfigs.SetupSpeed:
					message = CreateWriteMessage (config,Convert.ToByte( SteeringConfigCollection.SetupSpeed));
					break;
				default:
					break;
				}
				if (message != null) {
					_client.SendMessage ( message);
					Thread.Sleep (200);
				}
			}
		}

		public void ReadConfigs ()
		{
			foreach (SteeringConfigs config in Enum.GetValues(typeof(SteeringConfigs)))
			{
				if (config == SteeringConfigs.Non || config == SteeringConfigs.Base) {
					continue;
				}
				var message = CreateReadMessage (config);
				_client.SendMessage ( message);
				Thread.Sleep (200);
			}
		}
		#endregion

		ArduinoMessage CreateReadMessage(SteeringConfigs config)
		{
			ArduinoMessage message = new ArduinoMessage {
				LengthByte = 0x02,
				TypeByte = (byte)SteeringConfigs.Base,
				Payload = new byte[]{(byte)config,(byte)SteeringBaseBytes.Read}
			};
			return message;
		}

		ArduinoMessage CreateWriteMessage(SteeringConfigs config,byte value)
		{
			ArduinoMessage message = new ArduinoMessage {
				LengthByte = 0x03,
				TypeByte = (byte)SteeringConfigs.Base,
				Payload = new byte[]{(byte)config,(byte)SteeringBaseBytes.Write,value}
			};
			return message;
		}
	}
}

