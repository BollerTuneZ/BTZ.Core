using System;
using Communication.Infrastructure;
using Infrastructure;
using log4net;
using System.Threading;


namespace BollerTuneZCore
{
	public class Main
	{
		static readonly ILog s_log = LogManager.GetLogger (typeof(Main));
		readonly ISteeringProcessor _steeringProcessor;
		readonly ISteeringConfigMessageProcessor _steeringConfigProcessor;
		readonly IBTZJoyStickController _joyStick;
		DateTime lastTimeSetupPressed = DateTime.Now;
		DateTime lastTimeEnabledPressed = DateTime.Now;
		bool IsEnabled = false;

		public Main (ISteeringProcessor _steeringProcessor, ISteeringConfigMessageProcessor _steeringConfigProcessor, IBTZJoyStickController _joyStick)
		{
			this._steeringProcessor = _steeringProcessor;
			_steeringProcessor.Initialize ();
			this._steeringConfigProcessor = _steeringConfigProcessor;
			this._joyStick = _joyStick;
		}

		public void Run()
		{
			s_log.Info ("BollerTuneZ OS 1.0.1");
			Initialize ();

				while (true) {
					var input = Console.ReadLine();
				}
			
		}

		void Initialize()
		{
			s_log.Error ("Initializing");
			if (!_joyStick.Initialize()) {
				s_log.Error ("Could not Initialize Joystick");
				//return;
			}
			s_log.Error ("Initialized");

			_joyStick.OnPowerChanged += OnPowerChanged;
			_joyStick.OnSteeringChanged += OnSteeringPositionChanged;
			_joyStick.OnSpecialChanged += OnSpecialButtonChanged;
			_joyStick.Run ();
		}

		#region JoyStick Events
		void OnSpecialButtonChanged (object sender, EventArgs e)
		{
			SpecialButtonEventArgs args = (SpecialButtonEventArgs)e;
			//Console.WriteLine(String.Format("ButtonKey {0}, Value {1}",args.Key,args.Triggered));
			if (args.Key == 8) {
				if (args.Triggered) {
					if ((DateTime.Now.Subtract (lastTimeSetupPressed)).Seconds < 1) {
						s_log.Info ("Read configs");
						_steeringConfigProcessor.ReadConfigs ();
					}
					lastTimeSetupPressed = DateTime.Now;						
				}
			} else if (args.Key == 0) {
				if (args.Triggered) {
					if ((DateTime.Now.Subtract (lastTimeEnabledPressed)).Seconds < 1) {
						if (IsEnabled) {
							IsEnabled = false;
						} else {
							IsEnabled = true;
						}
						s_log.Info (String.Format ("Set Enabled to {0}", IsEnabled));
						_steeringProcessor.SetEnabled (IsEnabled);
					}
					lastTimeEnabledPressed = DateTime.Now;	
				}
			}else if (args.Key == 1) {
				if (args.Triggered) {
					s_log.Info ("StartSetup");
					_steeringProcessor.StartSetup ();
				}
			
			} else if (args.Key == 2) {
				if (args.Triggered) {
					s_log.Info ("Changed SetupLevel");
					_steeringProcessor.ChangeSetupLevel ();
				}
			}
		}

		void OnSteeringPositionChanged (object sender, EventArgs e)
		{
			SoftControlEventArgs args = (SoftControlEventArgs)e;
			if (IsEnabled) {
				s_log.Info (String.Format ("Change position to {0}", args.Value));
				_steeringProcessor.Steer (args.Value);
			}
		}

		void OnPowerChanged (object sender, EventArgs e)
		{
			
		}
		#endregion
	}
}

