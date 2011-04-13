#ifndef _ARGONMESSAGEBOARDMANAGER_HEADER_
#define _ARGONMESSAGEBOARDMANAGER_HEADER_

#include "ArgonSingleton.h"

namespace Argon
{
	class ArgonStandard MessageBoardManager : public singleton<MessageBoardManager>
	{
		friend singleton;
	public:

		///(BOOL)
		///
		///Add a messageboard to the manager so others can gain access to it
		///
		///Param MessageBoard: The message board that will be added
		bool AddMessageBoard(IMessageBoard* MessageBoard);
		
		///(BOOL)
		///
		///Remove a message board it will no longer be able to post messages
		///
		///Param MessageBoard: The message board that will be added
		bool RemoveMessageBoard(IMessageBoard* MessageBoard);
		
		///(BOOL)
		///
		///Remove a message board, it will no longer be able to post messages
		///
		///Param Name: The Name of the message board that will be removed
		bool RemoveMessageBoard(QString Name);

	protected:
		MessageBoardManager();
		~MessageBoardManager();


		Vector<IMessageBoard*> m_MessageBoards;
	}; //Class
} //Namespace

#endif //_ARGONMESSAGEBOARDMANAGER_HEADER_