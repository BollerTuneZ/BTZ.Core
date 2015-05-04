using System;

namespace Communication.Infrastructure
{
	/// <summary>
	/// Übergibt befehle an den Arduino
	/// </summary>
	public interface ISteeringProcessor
	{
		void Steer(int value);

		void Initialize();
	}
}

