#include "ArgonWindowsDll.h"

namespace Argon
{
	WindowsDll::WindowsDll(String Name, HINSTANCE Component) 
		: m_Name(Name),
		m_Component(Component)
	{
	}

	WindowsDll::~WindowsDll()
	{

	}

	/// Get the Name of this Dll
	String WindowsDll::GetName()
	{
		return m_Name;
	}

	/// Get the Instance or Component of this Dll
	HINSTANCE WindowsDll::GetComponent()
	{
		return m_Component;
	}

}//Namespace