#ifndef _LEVEL_HEADER_
#define _LEVEL_HEADER_

#include "XMLParse.h"

class Level : public XMLParse
{
public:
	Level();
	~Level();

	void createLevel();

	void parseLevelFile(const Ogre::String &FileName, const Ogre::String &groupName, Ogre::SceneManager *sceneMgr, Ogre::SceneNode *AttachNode = NULL, const Ogre::String &prependNode = "");

	void parseLevelObject(TiXmlElement *XMLNode,  Ogre::SceneNode *parent = 0);
	void processEntity(TiXmlElement *XMLNode, Ogre::SceneNode *parent);

	void parseScene(TiXmlElement *XMLRoot);

	void parseNodes(TiXmlElement *XMLNode);

	void destroyLevel();

	static Level& getSingleton();

	Ogre::SceneManager *getSceneManager() const;

protected:
	Ogre::String				mGroupName;
	Ogre::SceneManager*			mSceneMgr;
	Ogre::String				mPrependNode;
	Ogre::SceneNode				*mAttachNode;
};

#endif //_LEVEL_HEADER_