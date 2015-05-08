using System;
using Communication.Infrastructure;
using log4net;

namespace Communication
{
	public class MessagePacker : IMessagePacker
	{
		readonly static ILog s_log = LogManager.GetLogger (typeof(MessagePacker));  
		const byte StartByte = 0x01;
		const byte EndByte = 0xDE;

		public MessagePacker ()
		{
		}

		#region IMessagePacker implementation

		public ArduinoMessage PackMessage (byte[] payload)
		{
			if (payload == null || payload.Length < 4 ) {
				s_log.Warn ("received empty message");
				return null;
			}

			if (payload [0] != StartByte) {
				s_log.Warn (String.Format ("StartByte was {0}, expected {1}", payload [0], StartByte));
				return null;
			}

			ArduinoMessage message = new ArduinoMessage () {
				TypeByte = payload[1],
				LengthByte = payload[2]
			};

			byte[] data = new byte[message.LengthByte];

			for (int i = 0; i < data.Length; i++) {
				data[0] = payload [i + 3];
			}
			return message;
		}
		#endregion
	}
}

