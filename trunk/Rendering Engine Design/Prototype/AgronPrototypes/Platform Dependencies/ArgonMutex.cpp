#include "ArgonMutex.h"

Argon::Mutex::Mutex()
{
}

Argon::Mutex::~Mutex()
{
}

void Argon::Mutex::Lock()
{
	LockImpl();
}

void Argon::Mutex::Unlock()
{
	UnlockImpl();
}
