using System;

namespace Communication.Infrastructure
{
	public class ArduinoMessage
	{
		const byte StartByte = 0x01;
		const byte EndByte = 0xDE;
		public ArduinoMessage ()
		{
		}

		public byte LengthByte{ get; set; }
		public byte TypeByte{ get; set; }
		public byte[] Payload{ get; set; }
	}
}

