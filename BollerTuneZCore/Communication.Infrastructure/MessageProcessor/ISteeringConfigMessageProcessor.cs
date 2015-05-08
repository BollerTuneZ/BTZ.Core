using System;

namespace Communication.Infrastructure
{
	/// <summary>
	/// I steering config message processor.
	/// </summary>
	public interface ISteeringConfigMessageProcessor
	{
		void WriteConfigs();
		void ReadConfigs();
	}
}

