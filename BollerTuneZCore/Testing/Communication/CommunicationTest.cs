using System;
using Communication.Infrastructure;
using System.Threading;

namespace Testing
{
	public class CommunicationTest
	{
		IUDPService _service;
		IUDPClientService _clientService;
		const string ArduinoHostName = "192.168.2.177";
		const int ArduinoPort = 8888;
		private object thisLock = new object ();


		public CommunicationTest ()
		{
			_service = TinyIoC.TinyIoCContainer.Current.Resolve<IUDPService> ();
			_clientService = TinyIoC.TinyIoCContainer.Current.Resolve<IUDPClientService> ();
			Init ();
		}

		void Init()
		{
			_service.OnReveicedData += OnDataReceived;
			new Thread(() =>
				_service.Run (9050)).Start();
		}

		public void RunTests()
		{
			while (true) {

				Thread.Sleep (500);
				lock (thisLock) {
					ArduinoMessage messageRead = new ArduinoMessage { 
						LengthByte = Convert.ToByte (2),
						TypeByte = Convert.ToByte ('F'),
						Payload = new byte[]{ Convert.ToByte ('I'), Convert.ToByte ('R') }
					};
					_clientService.SendMessage ( messageRead);
				}
			
				Thread.Sleep (1000);
				lock (thisLock) {
					ArduinoMessage messageSet = new ArduinoMessage { 
						LengthByte = Convert.ToByte (3),
						TypeByte = Convert.ToByte ('F'),
						Payload = new byte[]{ Convert.ToByte ('I'), Convert.ToByte ('W'), Convert.ToByte ('Y') }
					};
					_clientService.SendMessage ( messageSet);
				}

			}

		}

		void OnDataReceived (object sender, EventArgs e)
		{
			lock (thisLock) {
				DataEventArgs args = (DataEventArgs)e;
				string hex = BitConverter.ToString (args.Data);
				Console.WriteLine (String.Format ("Daten erhalten um {0}, {1}", DateTime.Now.TimeOfDay, hex));


			}
		}
	}
}

