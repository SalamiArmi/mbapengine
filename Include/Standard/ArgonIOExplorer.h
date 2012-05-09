#ifndef _ARGONIOEXPLORER_HEADER_
#define _ARGONIOEXPLORER_HEADER_

#include <Standard/ArgonString.h>
#include <Interface/IOStream.h>

namespace Argon
{
	//>> OUT
	//<< IN 

	class ArgonStandard IOExplorer
	{
	public:
		IOExplorer(IOStream* Stream);
		~IOExplorer();

		///OPERATOR <<(IOEXPLORER)
		///
		///Write a String to the Stream
		///
		///Param Parse: The Value that will be Written into the $IOStream$
		IOExplorer& operator <<(String Parse);

		///OPERATOR >>(IOEXPLORER)
		///
		///Read a String from the Stream
		///
		///Param Parse: A reference to a variable that will have a value pushed into from the $IOStream$
		IOExplorer& operator >>(String &Parse);

		///OPERATOR <<(IOEXPLORER)
		///
		///Write a unsigned long to the Stream
		///
		///Param Parse: The Value that will be Written into the $IOStream$
		IOExplorer& operator <<(ulong Parse);

		///OPERATOR >>(IOEXPLORER)
		///
		///Read a unsigned long from the Stream
		///
		///Param Parse: A reference to a variable that will have a value pushed into from the $IOStream$
		IOExplorer& operator >>(ulong &Parse);

		///OPERATOR <<(IOEXPLORER)
		///
		///Write a long to the Stream
		///
		///Param Parse: The Value that will be Written into the $IOStream$
		IOExplorer& operator <<(long Parse);

		///OPERATOR >>(IOEXPLORER)
		///
		///Read a long from the Stream
		///
		///Param Parse: A reference to a variable that will have a value pushed into from the $IOStream$
		IOExplorer& operator >>(long &Parse);

		///OPERATOR <<(IOEXPLORER)
		///
		///Write a long64 to the Stream
		///
		///Param Parse: The Value that will be Written into the $IOStream$
		IOExplorer& operator <<(long64 Parse);

		///OPERATOR >>(IOEXPLORER)
		///
		///Read a long64 from the Stream
		///
		///Param Parse: A reference to a variable that will have a value pushed into from the $IOStream$
		IOExplorer& operator >>(long64 &Parse);

		///OPERATOR <<(IOEXPLORER)
		///
		///Write a ulong64 to the Stream
		///
		///Param Parse: The Value that will be Written into the $IOStream$
		IOExplorer& operator <<(ulong64 Parse);

		///OPERATOR >>(IOEXPLORER)
		///
		///Read a ulong64 from the Stream
		///
		///Param Parse: A reference to a variable that will have a value pushed into from the $IOStream$
		IOExplorer& operator >>(ulong64 &Parse);

		///OPERATOR <<(IOEXPLORER)
		///
		///Write a unsigned short to the Stream
		///
		///Param Parse: The Value that will be Written into the $IOStream$
		IOExplorer& operator <<(ushort Parse);

		///OPERATOR >>(IOEXPLORER)
		///
		///Read a unsigned short from the Stream
		///
		///Param Parse: A reference to a variable that will have a value pushed into from the $IOStream$
		IOExplorer& operator >>(ushort &Parse);

		///OPERATOR <<(IOEXPLORER)
		///
		///Write a short to the Stream
		///
		///Param Parse: The Value that will be Written into the $IOStream$
		IOExplorer& operator <<(short Parse);

		///OPERATOR >>(IOEXPLORER)
		///
		///Read a short from the Stream
		///
		///Param Parse: A reference to a variable that will have a value pushed into from the $IOStream$
		IOExplorer& operator >>(short &Parse);

		///OPERATOR <<(IOEXPLORER)
		///
		///Write a float to the Stream
		///
		///Param Parse: The Value that will be Written into the $IOStream$
		IOExplorer& operator <<(float Parse);

		///OPERATOR >>(IOEXPLORER)
		///
		///Read a float from the Stream
		///
		///Param Parse: A reference to a variable that will have a value pushed into from the $IOStream$
		IOExplorer& operator >>(float &Parse);

		///OPERATOR <<(IOEXPLORER)
		///
		///Write a unsigned int to the Stream
		///
		///Param Parse: The Value that will be Written into the $IOStream$
		IOExplorer& operator <<(uint Parse);

		///OPERATOR >>(IOEXPLORER)
		///
		///Read a unsigned int from the Stream
		///
		///Param Parse: A reference to a variable that will have a value pushed into from the $IOStream$
		IOExplorer& operator >>(uint &Parse);

		///OPERATOR <<(IOEXPLORER)
		///
		///Write a int to the Stream
		///
		///Param Parse: The Value that will be Written into the $IOStream$
		IOExplorer& operator <<(int Parse);

		///OPERATOR >>(IOEXPLORER)
		///
		///Read a int from the Stream
		///
		///Param Parse: A reference to a variable that will have a value pushed into from the $IOStream$
		IOExplorer& operator >>(int &Parse);

	private:
		IOStream* m_Stream;
	};

} //Namespace

#endif //_ARGONIOEXPLORER_HEADER_