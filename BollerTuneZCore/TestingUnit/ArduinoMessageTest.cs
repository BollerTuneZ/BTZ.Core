using System;
using NUnit.Framework;
using Communication.Infrastructure;

namespace TestingUnit
{
	[TestFixture ()]
	public class ArduinoMessageTest
	{
		[Test ()]
		public void CreateMessages()
		{
			ArduinoMessage message;
			message = new ArduinoMessage ();
			message.LengthByte = 0x01;
			message.TypeByte = (byte)Communication.Infrastructure.SteeringState.Base;
				message.Payload = new byte[] {
					(byte)Communication.Infrastructure.SteeringState.Enabled,
					(byte)SteeringBaseBytes.Write,
					Convert.ToByte ('Y')
				};

			Assert.AreEqual (0x43, message.TypeByte);
		}

	}
}

