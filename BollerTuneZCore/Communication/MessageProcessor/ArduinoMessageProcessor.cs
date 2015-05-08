using System;
using Communication.Infrastructure;

namespace Communication
{
	/// <summary>
	/// Jonas Ahlf 03.05.2015 00:41:12
	/// </summary>
	public class ArduinoMessageProcessor : IArduinoMessageProcessor
	{
		public ArduinoMessageProcessor ()
		{
		}

		#region IArduinoMessageProcessor implementation

		public ArduinoMessage ParseMessage (byte[] rawData)
		{
			throw new NotImplementedException ();
		}

		public byte[] CreateMessage (PackTypes Type, object payload)
		{
			throw new NotImplementedException ();
		}

		#endregion
	}
}

