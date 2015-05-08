using System;

namespace Infrastructure
{
	/// <summary>
	/// Serialisiert und Deserialisiert Objecte
	/// Jonas Ahlf 02.05.2015 23:51:32
	/// </summary>
	public interface IJsonHelper
	{
		/// <summary>
		/// Serialisiert ein objekt und gibt es als Json
		/// </summary>
		/// <returns>The to json.</returns>
		/// <param name="obj">Object.</param>
		string ObjectToJson(object obj);
		/// <summary>
		/// Deserialization the specified jsonObject.
		/// </summary>
		/// <param name="jsonObject">Json object.</param>
		/// <typeparam name="Tobject">The 1st type parameter.</typeparam>
		Tobject Deserialization<Tobject> (string jsonObject);
	}
}

