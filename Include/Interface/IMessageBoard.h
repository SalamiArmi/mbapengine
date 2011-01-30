#ifndef _IMESSAGEBOARD_HEADER_
#define _IMESSAGEBOARD_HEADER_

#include "IMessageBoardReader.h"
#include "IComponent.h"
#include <Standard/ArgonString.h>
#include <Standard/ArgonAny.h>


namespace Argon
{
	class IMessageBoardReader;

	DeclareBasedInterface(IMessageBoard, IComponent)

		enum MessageType
		{
			MESSAGETYPE_Critical = 0,	//Must be preformed
			MESSAGETYPE_Debug,			//Debug Information
			MESSAGETYPE_Preformance,	//Preformance Information
		};

		///ADDREADER(VOID)
		///
		///Add a message reader for this message board
		///
		///Param Reader: The message board reader that will recieve messages when a message is posted
		virtual void	AddReader(IMessageBoardReader* Reader)			= 0;

		///REMOVEREADER(VOID)
		///
		///Remove the specified reader from this message board
		///
		///Param Reader: The Reader that will be removed from this message board
		virtual void	RemoveReader(IMessageBoardReader* Reader)		= 0;

		///POSTMESSAGE(VOID)
		///
		///Post a message to this message board
		///Once posted the message will be sent to all IMessageBoardReaders
		///
		///Param Message: The message that will be passed around to all readers
		///Param Type: The state of the message this will determin if the readers will handle the message
		virtual void	PostMessage(Any Message, MessageType Type)		= 0;

		///REMOVEMESSAGE(VOID)
		///
		///Remove the desired message from the Message board
		///
		///Param Message: The message that will be removed from the Board
 		virtual void	RemoveMessage(String Message)					= 0;

	EndInterface(IMessageBoard) //Interface
} //Namespace

#endif //_IMESSAGEBOARD_HEADER_