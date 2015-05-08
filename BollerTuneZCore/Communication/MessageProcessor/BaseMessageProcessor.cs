using System;
using Communication.Infrastructure;
using Infrastructure;
using TinyIoC;

namespace Communication
{
	public class BaseMessageProcessor : IBaseMessageProcessor
	{
		private IJsonHelper _jsonHelper;

		public BaseMessageProcessor ()
		{
			_jsonHelper = TinyIoCContainer.Current.Resolve<IJsonHelper> ();
		}


		#region IBaseMessageProcessor implementation

		public string ProcessMessage (string data)
		{
			throw new NotImplementedException ();
		}
		#endregion
	}
}

