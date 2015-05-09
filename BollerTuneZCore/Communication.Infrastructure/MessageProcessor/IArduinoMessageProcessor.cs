using System;

namespace Communication.Infrastructure
{
	public interface IArduinoMessageProcessor
	{
		ArduinoMessage ParseMessage(byte[] rawData);

		byte[] CreateMessage(PackTypes Type, object payload);
	}
}

