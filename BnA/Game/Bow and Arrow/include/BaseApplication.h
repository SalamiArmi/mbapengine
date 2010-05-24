#ifndef _BASEAPPLICATION_HEADER_
#define _BASEAPPLICATION_HEADER_

class BaseApplication
{
public:
	virtual ~BaseApplication() {};
	virtual void init() = 0;
	virtual void update(Ogre::Real deltaT) = 0;
	virtual void exit() = 0;
	
	virtual void xboxInput(Ogre::Real deltaT) = 0;
};

#endif //_BASEAPPLICATION_HEADER_