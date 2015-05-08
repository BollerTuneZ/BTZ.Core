using System;

namespace Infrastructure
{
	public static class SteeringConfigCollection
	{
		public static char InputType{get;set;}

		public static int MaxSpeed{get;set;}
		public static int MinSpeed{get;set;}
		public static int MaxPosition{get;set;}
		public static int Center{get;set;}
		public static int SetupSpeed{get;set;}
		public static char LeftOn{get;set;}
		public static char RightOn{get;set;}
		public static char LeftOff{get;set;}
		public static char RightOff{get;set;}
		public static char DirLeft{get;set;}
		public static char DirRight{get;set;}
		public static char InvertDirection{get;set;}
	}
}

