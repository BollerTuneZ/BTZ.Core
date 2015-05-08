using System;

namespace Communication.Infrastructure
{
	/// <summary>
	/// Übergibt befehle an den Arduino
	/// </summary>
	public interface ISteeringProcessor
	{
		void Steer(int value);

		void Initialize();

		TObject ReadConfig<TObject>(SteeringConfigs config);

		bool SetConfig<TObject> (SteeringConfigs configs, TObject tObject);
	}
}

