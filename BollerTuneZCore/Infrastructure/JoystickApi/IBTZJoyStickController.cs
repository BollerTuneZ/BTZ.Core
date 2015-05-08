using System;

namespace Infrastructure
{
	/// <summary>
	/// Abgewandelte klasse die IJoyStickHandler benötigt,
	/// und nur relevante Daten liefert
	/// </summary>
	public interface IBTZJoyStickController
	{
		event EventHandler OnSteeringChanged;
		event EventHandler OnPowerChanged;
		event EventHandler OnSpecialChanged;

		bool Initialize();

		void Run();
	}
}

