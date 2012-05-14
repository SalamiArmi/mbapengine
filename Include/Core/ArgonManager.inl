template<typename Resource>
inline Manager<Resource>::~Manager()
{
	m_Resources.Clear();
}

template<typename Resource>
inline Resource* Manager<Resource>::GetResource(size_t Index)
{
	ArgonAssert(m_Resources.Size() > Index);
	return (*(m_Resources.Begin() + Index));
}

template<typename Resource>
inline Resource* Manager<Resource>::GetResource(String Name, bool Create)
{
	for(Vector<Resource*>::Iterator it = m_Resources.Begin(); it != m_Resources.End(); ++it)
	{
		if((*it)->GetName() == Name)
		{
			return (*it);
		}
	}


	if(Create)
	{
		Resource* r = CreateResource(Name);
		return r;
	}

	return NULL;
}

template<typename Resource>
inline size_t Manager<Resource>::GetResourceCount()
{
	return m_Resources.Size();
}

template<typename Resource>
inline int Manager<Resource>::GetResourceIndex(String Name)
{
	for(size_t Index = 0; Index < m_Resources.Size(); ++Index)
	{
		if(m_Resources[Index]->GetName() == Name)
		{
			return (int)Index;
		}
	}
	return -1;
}

template<typename Resource>
inline bool Manager<Resource>::ContainsResource(String Name)
{
	for(Vector<Resource*>::Iterator it = m_Resources.Begin(); it != m_Resources.End(); ++it)
	{
		if((*it)->GetName() == Name)
		{
			return true;
		}
	}
	return false;
}

template<typename Resource>
inline bool Manager<Resource>::RemoveResource(size_t Index)
{
	if(m_Resources.Size() > Index)
	{
		m_Resources.Erase(m_Resources.Begin() + Index);
		return true;
	}
	return false;
}

template<typename Resource>
inline bool Manager<Resource>::RemoveResource(String Name)
{
	for(Vector<Resource*>::Iterator it = m_Resources.Begin(); it != m_Resources.End(); ++it)
	{
		if((*it)->GetName() == Name)
		{
			m_Resources.Erase(it);
			return true;
		}
	}
	return false;
}

template<typename Resource>
inline bool Manager<Resource>::RemoveResource(Resource* Remove)
{
	for(Vector<Resource*>::Iterator it = m_Resources.Begin(); it != m_Resources.End(); ++it)
	{
		if((*it) == Remove)
		{
			m_Resources.Erase(it);
			return true;
		}
	}
	return false;
}

template<typename Resource>
inline Resource* Manager<Resource>::CreateResource(String Name)
{
	Resource* r = new Resource(Name);
	return r;
}