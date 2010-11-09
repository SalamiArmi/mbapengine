#ifndef _ARGONANY_HEADER_
#define _ARGONANY_HEADER_

#include <algorithm>
#include <typeinfo>

namespace Argon
{
	class Any
	{
	public:
		
		Any() 
			: m_Content(NULL)
		{

		}

		template<typename ValueT> explicit Any(const ValueT& Value) 
			: m_Content(new Holder<ValueT>(Value))
		{

		}

		Any(const Any& RHS)
			: m_Content(RHS.m_Content ? RHS.m_Content->Clone() : 0 )
		{

		}

		~Any()
		{
			delete m_Content;
		}


		///ISEMPTY(BOOL)
		///
		///Is the current content NULL
		///
		///No Params:
		bool IsEmpty() const
		{
			return !m_Content;
		}

		///GETTYPE(TYPE_INFO)
		///
		/// Get the type of content
		///
		///No Params:
		const std::type_info& GetType() const
		{
			return m_Content ? m_Content->GetType() : typeid(void);
		}

	private:

		class PlaceHolder
		{
		public:
			///CLONE(VOID)
			///
			/// Clone the current place holder
			///
			///No Params:
			virtual PlaceHolder* Clone() const = 0;
			
			///WRITETOSTREAM(VOID)
			///
			///Write the Value and Name to a file
			///This only supports XML
			///
			///No Params:
			//virtual void WriteToStream(const FILE* File) = 0; //TODO XML Reader and Writer

			///GETTYPE(STD::TYPE_INFO)
			///
			///Get the Type info for this type
			///
			///No Params:
			virtual std::type_info& GetType() const = 0;
		};

		template<typename T> class Holder : public PlaceHolder
		{
		public:
			Holder(const T& Value) :
			  m_Held(Value)
			{
			}

			PlaceHolder* Clone() const
			{
				return new Holder(m_Held);
			}

			std::type_info& GetType() const
			{
				return typeid(T);
			}

			T m_Held;
		};

		///OPERATOR()(TYPENAME VALUETYPE)
		///
		///Cast the type
		///
		///No Params:
		template<typename ValueType> ValueType operator()() const
		{
			if(!m_Content)
			{
				//throw Argon Exception
			}
			else if(GetType() == typeid(ValueType))
			{
				return static_cast<Any::Holder<ValueType>*>(m_Content)->m_Held;
			}
			else
			{
				//Throw Argon Exception
			}
		}

	protected:

		template<typename T> friend T* AnyCast(Any*);

		PlaceHolder* m_Content;
	};

	template<typename T> T* AnyCast(Any* RHS)
	{
		return RHS && RHS->GetType() == typeid(T) ? & static_cast<Any::Holder<T>*>(RHS->m_Content) : 0;
	}

	template<typename T> const T* AnyCast(const Any* RHS)
	{
		return AnyCast<T>(const_cast<Any*>(RHS));
	}

	template<typename T> T AnyCast(const Any& RHS)
	{
		const T* Result = AnyCast<T>(&RHS);
		if(!Result)
		{
			//Throw Argon Exception
		}
		return *Result;
	}

} //Namespace

#endif //_ARGONANY_HEADER_