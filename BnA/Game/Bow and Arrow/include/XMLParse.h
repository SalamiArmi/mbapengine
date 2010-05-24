#ifndef _XMLPARSE_HEADER_
#define _XMLPARSE_HEADER_

#include "tinyxml.h"

///TODO in the future make this a templated class

class XMLParse
{
public:
	///PARSEVECTOR3
	///
	///Parse a xml Vector3 into a Ogre Vector3
	///
	///Param XmlNode: The node to be checked against
	Ogre::Vector3 parseVector3(TiXmlElement *XmlNode);

	///PARSEQUATERNION
	///
	///Parse a xml Quaternion into a Ogre Quaternion
	///
	///Param XmlNode: The node to be checked against
	Ogre::Quaternion parseQuaternion(TiXmlElement *XMLNode);

	///GETATTRIBUTE
	///
	///
	///
	///Param XmlNode: The node to be checked against
	Ogre::String getAttribute(TiXmlElement *XMLNode, const Ogre::String parameter, const Ogre::String defaultValue = "");

	///GETATTRIBUTEREAL
	///
	///
	///A real is also known as a float
	///
	///Param XmlNode: The node to be checked against
	Ogre::Real getAttributeReal(TiXmlElement *XMLNode, const Ogre::String parameter, Ogre::Real defaultValue = 0);
};

#endif //_XMLPARSE_HEADER_