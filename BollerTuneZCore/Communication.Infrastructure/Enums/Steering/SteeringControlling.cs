using System;

namespace Communication.Infrastructure
{
	public enum SteeringControlling :byte
	{
		Base = 0x43,
		Turn = 0x54,
		MotorSpeed = 0x53,
		StartSetup = 0x73,
		SetToZero = 0x4F,
		ContinueSetup = 0x63,
		SetMaximumAndExit = 0x65,

	}
}

