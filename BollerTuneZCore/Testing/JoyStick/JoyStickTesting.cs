using System;
using Infrastructure;
namespace Testing
{
	public class JoyStickTesting
	{
		readonly IBTZJoyStickController _btzJoyStickController;

		public JoyStickTesting (IBTZJoyStickController _btzJoyStickController)
		{
			this._btzJoyStickController = _btzJoyStickController;
			this._btzJoyStickController.OnPowerChanged += OnPowerHasChanged;
			this._btzJoyStickController.OnSpecialChanged += OnSpecialButtonTriggered;
			this._btzJoyStickController.OnSteeringChanged += OnSteeringHasChanged;
		}

		public void Run()
		{
			_btzJoyStickController.Initialize ();
		}

		void OnSteeringHasChanged (object sender, EventArgs e)
		{
			SoftControlEventArgs args = (SoftControlEventArgs)e;
			Console.WriteLine (String.Format ("Steering changed to: {0}", args.Value));
		}

		void OnSpecialButtonTriggered (object sender, EventArgs e)
		{
			SpecialButtonEventArgs args = (SpecialButtonEventArgs)e;
			Console.WriteLine(String.Format("Specialbuttonstate: {0}",args.Triggered));
		}

		void OnPowerHasChanged (object sender, EventArgs e)
		{
			SoftControlEventArgs args = (SoftControlEventArgs)e;
			Console.WriteLine (String.Format ("Power changed to: {0}", args.Value));
		}
		
	}
}

