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

		public override string ToString ()
		{
			return string.Format ("[ArduinoMessage: LengthByte={0}, TypeByte={1}, Payload={2}]", LengthByte, TypeByte, Payload);
		}

	}
}

