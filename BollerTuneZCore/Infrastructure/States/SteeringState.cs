using System;

namespace Infrastructure
{
	public static class SteeringState
	{
		public static int CurrentSpeed{get;set;}

		public static char Enabled{get;set;}

		public static char IsRunning{get;set;}
		public static char Direction{get;set;}
		public static int EncoderMotor{get;set;}
		public static int EncoderSteering{get;set;}
		public static char RemotePosition{get;set;}

	}
}

