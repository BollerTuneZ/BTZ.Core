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

		/// <summary>
		/// Beginnt das Setup
		/// </summary>
		void StartSetup();
		/// <summary>
		/// Geht einen Schritt weiter im Setup
		/// </summary>
		void ChangeSetupLevel();
	}
}

