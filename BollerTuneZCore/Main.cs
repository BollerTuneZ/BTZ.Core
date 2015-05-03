using System;
using Communication.Infrastructure;

namespace BollerTuneZCore
{
	public class Main
	{
		IUDPService _joyStickService;
		IUDPClientService _clientService;

		public Main (IUDPService _joyStickService, IUDPClientService _clientService)
		{
			this._joyStickService = _joyStickService;
			this._clientService = _clientService;
		}

		void Init()
		{

		}

	}
}

