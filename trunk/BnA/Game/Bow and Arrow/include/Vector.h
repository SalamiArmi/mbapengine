#ifndef _STACK_HEADER_
#define _STACK_HEADER_

//Working with templates is easier in a single header for now

template <typename T> class Vector
{
public:

	Vector()
	{
		m_Top = 0;
		m_Empty = true;

		m_Stack = new T[m_Top];
	}


	~Vector()
	{
		delete [] m_Stack;
	}

	//Set non Templeted functions
	bool push_Back(T &Item)
	{
		m_Stack[++m_Top] = Item;
		return true;
	}

	bool pop_back(const T& Item)
	{
		if ( !m_Empty )
		{
			Item = m_Stack[top--];

			if ( m_Top == 0 || m_Count == 0 )
			{
				m_Empty = true;
			}

			return true;
		}
		return false;
	}

	bool removeAt(int Index)
	{
		//Remove the object at the index
		//And reshuffle all objects above this number

		//m_Stack[index]

	}

	bool isEmpty()
	{
		return m_Empty;
	}


	int getCount()
	{
		return m_Top;
	}

	bool Empty()
	{
		while ( m_Top > 0 )
		{
			m_Stack[top--];

			if ( m_Top == 0 || m_Count == 0 )
			{
				m_Empty = true;
			}
		}
	}

	T getLast()
	{
		return (* ( m_Stack[ m_Top ] ) );
	}

	T at(int Index)
	{
		return (* ( m_Stack[ Index ] ) );
	}

	T First()
	{
		return (* ( m_Stack[ 0 ] ) );
	}

private:

	int m_Top;
	bool m_Empty;

	T* m_Stack;
};

#endif //_STACK_HEADER_