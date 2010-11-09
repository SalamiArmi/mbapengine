#ifndef _IMESSAGEBOARDREADER_HEADER_
#define _IMESSAGEBOARDREADER_HEADER_

#include "IMessageBoard.h"

namespace Argon
{
	class IMessageBoard;

	DeclareBasedInterface(IMessageBoardReader, IArgonUnknown)
		
		///READMESSAGE(VOID)
		///
		///Read a posted message from the message board
		///
		///Param MessageBoard: The message board that send the message for the reader
		virtual void ReadMessage(IMessageBoard* MessageBoard, uint Message)	= 0;

	EndInterface(IMessageBoardReader) //Interface

} //Namespace

#endif //_IMESSAGEBOARDREADER_HEADER_