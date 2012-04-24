Mutex::Mutex()
{
}

Mutex::~Mutex()
{
}

void Mutex::Lock()
{
	LockImpl();
}

void Mutex::Unlock()
{
	UnlockImpl();
}