using System;

namespace Communication.Infrastructure
{
	public enum MessageType
	{
		/*Lenkung*/
		Steering_position,
		Steering_readPosition,
		Steering_setInputType,
		Steering_setMaxPower,

		/*Antrieb*/
		Engine_setDirection,
		Engine_setSpeed,
		Engine_readSpeed,
		Engine_readDirection
	}
}

