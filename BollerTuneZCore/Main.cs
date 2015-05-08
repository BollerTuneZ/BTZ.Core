using System;
using Communication.Infrastructure;
using Infrastructure;
using log4net;


namespace BollerTuneZCore
{
	public class Main
	{
		static readonly ILog s_log = LogManager.GetLogger (typeof(Main));
		readonly ISteeringProcessor _steeringProcessor;
		readonly ISteeringConfigMessageProcessor _steeringConfigProcessor;
		readonly IBTZJoyStickController _joyStick;

		public Main (ISteeringProcessor _steeringProcessor, ISteeringConfigMessageProcessor _steeringConfigProcessor, IBTZJoyStickController _joyStick)
		{
			this._steeringProcessor = _steeringProcessor;
			this._steeringConfigProcessor = _steeringConfigProcessor;
			this._joyStick = _joyStick;
		}

		public void Run()
		{
			s_log.Info ("BollerTuneZ OS 1.0.1");

		}

		void Initialize()
		{
			if (!_joyStick.Initialize()) {
				s_log.Error ("Could not Initialize Joystick");
				return;
			}

			_joyStick.OnPowerChanged += OnPowerChanged;
			_joyStick.OnSteeringChanged += OnSteeringPositionChanged;
			_joyStick.OnSpecialChanged += OnSpecialButtonChanged;
		}

		#region JoyStick Events
		void OnSpecialButtonChanged (object sender, EventArgs e)
		{
			
		}

		void OnSteeringPositionChanged (object sender, EventArgs e)
		{
			
		}

		void OnPowerChanged (object sender, EventArgs e)
		{
			
		}
		#endregion
	}
}

