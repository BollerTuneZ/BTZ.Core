using System;

namespace Communication.Infrastructure
{
	/// <summary>
	/// Basis MessageProcessor der byte[] Daten entgegen nimmt und zurück gibt
	/// </summary>
	public interface IBaseMessageProcessor
	{
		string ProcessMessage(string data);
	}
}

