using System;

namespace Communication.Infrastructure
{
	public enum SteeringState: byte
	{
		Base = 0x53,
		CurrentPosition = 0x50,
		Enabled = 0x45,
		Running = 0x52,
		Direction = 0x44,
		EncoderMotor = 0x4D,
		EncoderSteering = 0x4E,
		RemotePosition = 0x54,
	}
}

