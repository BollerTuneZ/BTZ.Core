using System;

namespace Communication.Infrastructure
{
	public class DataEventArgs : EventArgs
	{
		public DataEventArgs ()
		{
		}
		public byte[] Data{ get; set; }
	}
}

