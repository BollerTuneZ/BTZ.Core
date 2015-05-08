using System;
using System.Collections.Generic;

namespace Communication.Infrastructure
{
	public static class EnumConverter
	{
		static Dictionary<byte,MessageType> _byteKey = new Dictionary<byte,MessageType>();
		static Dictionary<MessageType,byte> _enumKey = new Dictionary<MessageType,byte>();

		static EnumConverter ()
		{
			CreateByteKeyDictionary ();
			CreateEnumDictionary ();
		}

		public static MessageType ByteToMessageType(byte type)
		{
			return _byteKey [type];
		}

		public static byte MessageTypeToType(MessageType type)
		{
			return _enumKey [type];
		}


		static void CreateByteKeyDictionary()
		{
			_byteKey.Add (0x14, MessageType.Steering_position); //20
			_byteKey.Add (0x15, MessageType.Steering_readPosition); //21
			_byteKey.Add (0x16, MessageType.Steering_setInputType); //22
			_byteKey.Add (0x17, MessageType.Steering_setMaxPower); //23

			_byteKey.Add (0x1E, MessageType.Engine_readDirection); //30
			_byteKey.Add (0x1F, MessageType.Engine_readSpeed); //31
			_byteKey.Add (0x20, MessageType.Engine_setDirection); //32
			_byteKey.Add (0x21, MessageType.Engine_setSpeed); //33
		}

		static void CreateEnumDictionary()
		{
			_enumKey.Add (MessageType.Steering_position, 0x14);
			_enumKey.Add (MessageType.Steering_readPosition, 0x15);
			_enumKey.Add (MessageType.Steering_setInputType, 0x16);
			_enumKey.Add (MessageType.Steering_setMaxPower, 0x17);

			_enumKey.Add (MessageType.Engine_readDirection, 0x1E);
			_enumKey.Add (MessageType.Engine_readSpeed, 0x1F);
			_enumKey.Add (MessageType.Engine_setDirection, 0x20);
			_enumKey.Add (MessageType.Engine_setSpeed, 0x21);

		}
	}
}

