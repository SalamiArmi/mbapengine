#ifndef _ARGONATTRIBUTE_HEADER_
#define _ARGONATTRIBUTE_HEADER_

#include <Standard/ArgonVector.h>
#include <Standard/ArgonVector2.h>
#include <Standard/ArgonVector3.h>
#include <Standard/ArgonVector4.h>
#include <Standard/ArgonString.h>
#include <Standard/ArgonMatrix3.h>
#include <Standard/ArgonMatrix4.h>

#include <Standard/ArgonAny.h>

namespace Argon
{
	enum AttributeType
	{
		ATTRIBUTETYPE_Unknown,
		ATTRIBUTETYPE_Bool,
		ATTRIBUTETYPE_Integer,
		ATTRIBUTETYPE_Float,
		ATTRIBUTETYPE_Vector2,
		ATTRIBUTETYPE_Vector3,
		ATTRIBUTETYPE_Vector4,
		ATTRIBUTETYPE_Matrix3,
		ATTRIBUTETYPE_Matrix4,
		ATTRIBUTETYPE_String,
		ATTRIBUTETYPE_Texture2D,
		ATTRIBUTETYPE_Texture3D,
		ATTRIBUTETYPE_DepthStencil,
		ATTRIBUTETYPE_RenderTarget
	};

	class Attribute
	{
	public:

		class Listner
		{	
		public:
			Listner();
			~Listner();

			///VALUECHANGED(VOID)
			///
			///The value of a Attribute has changed
			///
			///Param Changed: The Attribute that has been changed
			void ValueChanged(Attribute* Changed);
		}; //Class

		Attribute(String Name, AttributeType Type);
		Attribute(String Name, AttributeType Type, Any Value);
		~Attribute();

		///GETNAME(STRING)
		///
		///Get the name of the attribute
		///
		///No Params:
		String GetName();

		///GETASBOOLEAN(BOOL)
		///
		///Get the internal value as a boolean
		///
		///No Params:
		bool GetAsBoolean();

		///GETASINTEGER(INT)
		///
		///Get the internal value value as a integer
		///
		///No Params:
		int GetAsInteger();

		///GETVALUE(TEMPLATE)
		///
		///Get the internal value value as a float
		///
		///No Params:
		float GetAsFloat();

		///GETASVECTOR2(VECTOR2)
		///
		///Get the internal value value as a Vector2
		///
		///No Params:
		Vector2 GetAsVector2();

		///GETASVECTOR3(VECTOR3)
		///
		///Get the internal value value as a Vector3
		///
		///No Params:
		Vector3 GetAsVector3();

		///GETASVECTOR4(VECTOR4)
		///
		///Get the internal value value as a Vector4
		///
		///No Params:
		Vector4 GetAsVector4();

		///GETASMATRIX3(MATRIX3)
		///
		///Get the internal value as a Matrix3
		///
		///No Params:
		Matrix3 GetAsMatrix3();

		///GETASMATRIX4(MATRIX4)
		///
		///Get the internal value as a Matrix4
		///
		///No Params:
		Matrix4 GetAsMatrix4();

		///GETASSTRING(STRING)
		///
		///Get the internal value as a String
		///
		///No Params:
		String GetAsString();

		///SETVALUE(VOID)
		///
		///Set the internal value
		///
		///Param Pass: The value in its native form
		void SetValue(Any& Value);

		///SETALUEFROMSTRING(VOID)
		///
		///Set the internal value from a string
		///
		///Param Value: The value in string form
		void SetValueFromString(String Value);

		///GETTYPE(UNSIGNEDINT)
		///
		///Get the type of Attribute this is
		///
		///No Params
		uint GetType();

		///ADDLISTNER(VOID)
		///
		///Add a listner to this attribute that will be called if the internal value changes
		///
		///Param Add: The listner that will start to receive messages
		void AddListner(Listner* Add);

		///REMOVELISTNER(VOID)
		///
		///Remve a listner from this attribute it will no longer receive messages
		///
		///Param Remove: The listner that will no longer receive messages
		void RemoveListner(Listner* Remove);

	protected:
		String				m_Name;
		Any					m_Value;

		uint				m_Type;

		Vector<Listner*>	m_Listners;
	}; //Class
} //Namespace

#endif //_ARGONATTRIBUTE_HEADER_