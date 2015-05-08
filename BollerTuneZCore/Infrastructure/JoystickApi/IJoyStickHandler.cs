using System;

namespace Infrastructure
{
	/// <summary>
	/// Empfängt Befehle vom Joystick
	/// </summary>
	public interface IJoyStickHandler
	{
		event EventHandler OnButtonTriggered;

		void Initialize();

		void Run();

	}
}

