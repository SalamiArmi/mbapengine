#ifndef _IOSTREAM_HEADER_
#define _IOSTREAM_HEADER_

#include "IArgonUnknown.h"

namespace Argon
{
	DeclareBasedInterface(IOStream, IArgonUnknown)

		enum Mode
		{
			MODE_Read,
			MODE_Write,
		}; //Enum

		///READ(BOOL)
		///
		///Read the length of bytes into the Bytes pointer.
		///
		///Param Bytes: A preallocated buffer of the size Length
		///Param Length: The total length of the preallocated buffer
		bool Read(char* Bytes, ulong Length);

		///WRITE(VOID)
		///
		///Write the bytes into the Steam
		///
		///Param Bytes: A preallocated buffer of the size Length
		///Param Length: The total length of the preallocated buffer
		void Write(const char* Bytes, ulong Length);

		///CLOSE(VOID)
		///
		///Close the Stream and release all stream resources.
		///
		///No Params:
		void Close();

		///SETPOSITION(BOOL)
		///
		///Set the current Read/Write position
		///
		///Param Position: The new Read/Write position
		bool SetPosition(ulong Position);

		///GETPOSITION(ULONG)
		///
		///Get the current Read/Write position
		///
		///No Params:
		ulong GetPosition();

		///GETLENGTH(ULONG)
		///
		///Get the total length of the stream
		///
		///No Params:
		ulong GetLength();

		///FLUSH(VOID)
		///
		///Flush the current buffer to the stream
		///
		///No Params:
		void Flush();

		///ATEND(BOOL)
		///
		///Is the Read/Write at the end of the file?
		///
		///No Params:
		bool AtEnd();

	EndInterface(IOStream) //Interface

} //Namespace

#endif