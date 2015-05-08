using System;

namespace Communication.Infrastructure
{
	public interface IUDPService
	{
		event EventHandler OnReveicedData;
		void Run(int port);
	}
}

