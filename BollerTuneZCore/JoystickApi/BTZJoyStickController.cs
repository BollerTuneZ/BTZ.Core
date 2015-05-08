using System;
using Infrastructure;

namespace JoystickApi
{
	public class BTZJoyStickController : IBTZJoyStickController
	{
		readonly IJoyStickHandler _joyStickHandler;

		const int Low = -32767;
		const int High = Low * (-1);

		#region ButtonValues
		static int SteeringPosition;
		static int PowerPosition;
		static int PowerPositionBackWards;
		static bool TempomatState;
		#endregion

		public BTZJoyStickController (IJoyStickHandler _joyStickHandler)
		{
			this._joyStickHandler = _joyStickHandler;
			this._joyStickHandler.OnButtonTriggered += OnJoyStickButtonTriggered;
		}

		void OnJoyStickButtonTriggered (object sender, EventArgs e)
		{
			JoyStickEventArgs args = (JoyStickEventArgs)e;
			if (args.Button == Buttons.Axis) {
				ProcessAxis (args);
			} else if (args.Button == Buttons.Button) {
				ProcessSpecialButtons (args);
			}
		}

		#region IBTZJoyStickController implementation

		public event EventHandler OnSteeringChanged;

		public event EventHandler OnPowerChanged;

		public event EventHandler OnSpecialChanged;

		public bool Initialize ()
		{
			_joyStickHandler.Initialize ();
			return true;
		}

		public void Run ()
		{
			_joyStickHandler.Run ();
		}
		#endregion

		void ProcessAxis(JoyStickEventArgs args)
		{
			if (args.Key == 5) {
				int mappedValue = (int)map (args.Value, Low, High, 0, 255);
				if (mappedValue != PowerPosition) {
					OnPowerChanged (this, new SoftControlEventArgs () {
						Value = mappedValue,
					});
				}
				PowerPosition = mappedValue;
			}  else if (args.Key == 2) {

				int mappedValue = -(int)map (args.Value, Low, High, 0, 255);
				if (mappedValue != PowerPositionBackWards) {
					OnPowerChanged (this, new SoftControlEventArgs () {
						Value = mappedValue,
					});
				}
				PowerPositionBackWards = mappedValue;
			}

			else if (args.Key == 0) {
				int mappedValue = (int)map (args.Value, Low, High, 0, 255);
				if (mappedValue != SteeringPosition) {
					OnSteeringChanged (this, new SoftControlEventArgs () {
						Value = mappedValue,
					});
				}
				SteeringPosition = mappedValue;
			}
		}

		void ProcessSpecialButtons(JoyStickEventArgs args)
		{
			//Console.WriteLine(String.Format("ButtonBTZ {0} : {1}",args.Key,args.Triggered));

			OnSpecialChanged (this, new SpecialButtonEventArgs () {
				Triggered = args.Triggered,
				Key = args.Key
			});
		}

		public static int Map (int value, int fromSource, int toSource, int fromTarget, int toTarget)
		{
			return (value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget;
		}

		private uint map(int x, int in_min, int in_max, int out_min, int out_max)
		{
			int Puls = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
			return (uint)Puls;
		}
	}
}

