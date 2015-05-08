using System;
using Infrastructure;
using Newtonsoft;
using Newtonsoft.Json;


namespace SerializationLib
{
	public class JsonHelper : IJsonHelper
	{
		public JsonHelper ()
		{
		}

		#region IJsonHelper implementation

		public string ObjectToJson (object obj)
		{
			return JsonConvert.SerializeObject (obj);
		}

		public Tobject Deserialization<Tobject> (string jsonObject)
		{
			return JsonConvert.DeserializeObject<Tobject> (jsonObject);
		}

		#endregion
	}
}

