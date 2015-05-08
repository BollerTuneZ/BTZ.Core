using System;

namespace Infrastructure
{
	public class JoyStickEventArgs : EventArgs
	{
		public JoyStickEventArgs ()
		{
		}

		public Buttons Button{get;set;}

		public byte Key{ get; set;}

		public bool Triggered{get;set;}

		public int Value{get;set;}
	}
}

