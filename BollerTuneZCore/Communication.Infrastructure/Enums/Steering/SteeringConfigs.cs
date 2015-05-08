using System;

namespace Communication.Infrastructure
{
	/// <summary>
	/// Typen für Lenkunskonfig
	/// Jonas Ahlf 08.05.2015 01:35:21
	/// </summary>
	public enum SteeringConfigs : byte
	{
		Non = 0x00,
		Base = 0x46,
		InputType = 0x49,
		MaximalSpeed = 0x57,
		MinimalSpeed = 0x53,
		Center = 0x43,
		SetupSpeed = 0x55,
		LeftOn = 0x71,
		LeftOff= 0x77,
		RightOn = 0x65,
		RightOff= 0x72,
		DirLeft= 0x4C,
		DirRight= 0x52,
		InvertDirection= 0x44
	}
}

