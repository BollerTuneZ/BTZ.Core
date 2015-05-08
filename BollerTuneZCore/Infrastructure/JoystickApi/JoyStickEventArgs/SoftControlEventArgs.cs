using System;

namespace Infrastructure
{
	public class SoftControlEventArgs : EventArgs
	{
		public SoftControlEventArgs ()
		{
		}

		public int Value{get;set;}
	}
}

