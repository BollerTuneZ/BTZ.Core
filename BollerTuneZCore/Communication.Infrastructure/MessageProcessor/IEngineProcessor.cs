using System;

namespace Communication.Infrastructure
{
	public interface IEngineProcessor
	{
		void Drive(int value);
		void SetEnabled(bool enabled);
	}
}

