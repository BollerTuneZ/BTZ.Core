using System;

namespace Infrastructure
{
	public class SpecialButtonEventArgs : EventArgs
	{
		public SpecialButtonEventArgs ()
		{
		}
		public int Key{ get; set;}
		public bool Triggered{get;set;}
	}
}

