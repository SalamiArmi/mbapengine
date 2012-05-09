inline Mutex::Mutex()
{
}

inline Mutex::~Mutex()
{
}

inline void Mutex::Lock()
{
	LockImpl();
}

inline void Mutex::Unlock()
{
	UnlockImpl();
}