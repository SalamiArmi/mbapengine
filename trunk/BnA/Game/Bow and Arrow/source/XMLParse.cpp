#include "Precompiled.h"
#include "XMLParse.h"

Ogre::Vector3 XMLParse::parseVector3(TiXmlElement *XmlNode)
{
	return Ogre::Vector3(
		Ogre::StringConverter::parseReal(XmlNode->Attribute("x")),
		Ogre::StringConverter::parseReal(XmlNode->Attribute("y")),
		Ogre::StringConverter::parseReal(XmlNode->Attribute("z")));
}


Ogre::Quaternion XMLParse::parseQuaternion(TiXmlElement *XMLNode)
{
	return Ogre::Quaternion(
		Ogre::StringConverter::parseReal(XMLNode->Attribute("qw")),
		Ogre::StringConverter::parseReal(XMLNode->Attribute("qx")),
		Ogre::StringConverter::parseReal(XMLNode->Attribute("qy")),
		Ogre::StringConverter::parseReal(XMLNode->Attribute("qz")));
}

Ogre::String XMLParse::getAttribute(TiXmlElement *XMLNode, const Ogre::String attrib, const Ogre::String defaultValue)
{
	if(XMLNode->Attribute(attrib.c_str()))
		return XMLNode->Attribute(attrib.c_str());
	else
		return defaultValue;
}

Ogre::Real XMLParse::getAttributeReal(TiXmlElement *XMLNode, const Ogre::String attrib, Ogre::Real defaultValue)
{
	if(XMLNode->Attribute(attrib.c_str()))
		return Ogre::StringConverter::parseReal(XMLNode->Attribute(attrib.c_str()));
	else
		return defaultValue;
}