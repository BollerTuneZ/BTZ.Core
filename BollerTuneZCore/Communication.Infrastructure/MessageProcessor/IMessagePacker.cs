using System;

namespace Communication.Infrastructure
{
	/// <summary>
	/// Packt byte daten zu ArduinoMessages
	/// </summary>
	public interface IMessagePacker
	{
		ArduinoMessage PackMessage(byte[] payload);
	}
}

