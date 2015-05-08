using System;

namespace Infrastructure
{
	public class SpecialButtonEventArgs : EventArgs
	{
		public SpecialButtonEventArgs ()
		{
		}

		public bool Triggered{get;set;}
	}
}

