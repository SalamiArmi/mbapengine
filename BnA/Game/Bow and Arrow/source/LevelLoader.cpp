#include "Precompiled.h"
#include "LevelLoader.h"
#include "SceneManager.h"
#include "PhysicsManager.h"

template<> Level* Ogre::Singleton<Level>::ms_Singleton = 0;

Level::Level()
{
}

Level::~Level()
{
}

void Level::createLevel()
{
	Ogre::Light* SunLight;
	SunLight = SceneManager::getSingleton().getSceneManager()->createLight("MainLight");
	SunLight->setPosition(2000,3000,1000);
	SunLight->setSpecularColour(1,1,1);
	SunLight->setDiffuseColour(1,1,1);
	SunLight->setDirection(-2,-3,-1);
	SunLight->setType(Ogre::Light::LT_DIRECTIONAL);

	//// Setup our shadows
	SceneManager::getSingleton().getSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
	SceneManager::getSingleton().getSceneManager()->setShadowFarDistance(100000);
	SceneManager::getSingleton().getSceneManager()->setShadowColour(Ogre::ColourValue(0.7, 0.7, 0.7));
}


void Level::parseLevelFile(const Ogre::String &FileName, const Ogre::String &groupName, Ogre::SceneManager *sceneMgr, Ogre::SceneNode *AttachNode, const Ogre::String &prependNode)
{
	mGroupName = groupName;
	mSceneMgr = sceneMgr;
	mPrependNode = prependNode;

	TiXmlDocument *mXMLDoc = 0;
	TiXmlElement *mXMLRoot = 0;

	try
	{
		Ogre::String basename, path;
		Ogre::StringUtil::splitFilename(FileName, basename, path);

		Ogre::DataStreamPtr spStream = Ogre::ResourceGroupManager::getSingleton().openResource(basename,groupName);

		Ogre::String data = spStream->getAsString();

		mXMLDoc = new TiXmlDocument();
		mXMLDoc->Parse(data.c_str());

		spStream->close();
		spStream.setNull();

		mXMLRoot = mXMLDoc->RootElement();

		mAttachNode = AttachNode;


		if(!mAttachNode)
			mAttachNode = mSceneMgr->getRootSceneNode();

		parseScene(mXMLRoot);

		delete mXMLDoc;
	}
	catch(Ogre::Exception e)
	{
		Ogre::LogManager::getSingleton().logMessage("Level failed to load");
		delete mXMLDoc;
	}
}

void Level::parseScene(TiXmlElement *XMLNode)
{
	TiXmlElement *element;

	element = XMLNode->FirstChildElement("nodes");
	if(element)
	{
		parseNodes(element);
	}
}

void Level::parseLevelObject(TiXmlElement *XMLNode,  Ogre::SceneNode *parent)
{
	Ogre::Vector3 spawnPosition;
	Ogre::Quaternion spawnRotation;
	Ogre::SceneNode* node;

	Ogre::String name = getAttribute(XMLNode, "name");
	Ogre::String mesh = name;

	if(name.empty())
	{
		// Let Ogre choose the name
		if(parent)
			node = parent->createChildSceneNode();
		else
			node = mAttachNode->createChildSceneNode();
	}
	else
	{
		// Provide the name
		if(parent)
			node = parent->createChildSceneNode(name);
		else
			node = mAttachNode->createChildSceneNode(name);
	}

	Ogre::String id = getAttribute(XMLNode, "id");

	TiXmlElement *element;

	element = XMLNode->FirstChildElement("position");
	if(element)
	{
		spawnPosition = parseVector3(element);
		node->setPosition(spawnPosition);
		node->setInitialState();
	}

	element = XMLNode->FirstChildElement("rotation");
	if(element)
	{
		node->setOrientation(parseQuaternion(element));
		spawnRotation = parseQuaternion(element);	
	}

	element = XMLNode->FirstChildElement("scale");
	if(element)
	{
		node->setScale(parseVector3(element));
		node->setInitialState();
	}

	element = XMLNode->FirstChildElement("node");
	while(element)
	{
		parseLevelObject(element, node);
		element = element->NextSiblingElement("node");
	}

	element = XMLNode->FirstChildElement("entity");
	while(element)
	{
		processEntity(element, node);
		element = element->NextSiblingElement("entity");
	}
}

void Level::processEntity(TiXmlElement *XMLNode, Ogre::SceneNode *parent)
{
	Ogre::String name = getAttribute(XMLNode, "name");
	Ogre::String meshFile = getAttribute(XMLNode, "meshFile");

	TiXmlElement *element;
	Ogre::Entity *entity = 0;

	try
	{
		entity = mSceneMgr->createEntity(name, meshFile);
		entity->setCastShadows(true);

		PhysicsManager::instance()->createConvexMesh(entity);

		element = XMLNode->FirstChildElement("subentities");
		if(element)
		{
			element = element->FirstChildElement("subentity");
			while (element)
			{
				Ogre::SubEntity *subEnt;

				Ogre::String materialFile = getAttribute(element, "materialName");
				unsigned int index = Ogre::StringConverter::parseInt(getAttribute(element,"index"));

				subEnt = entity->getSubEntity(index);
				subEnt->setMaterialName(materialFile);

				element = element->NextSiblingElement("subentity");		
			}
		}
		entity->setRenderingDistance(1000);
		parent->attachObject(entity);

	}
	catch(Ogre::Exception e)
	{
		Ogre::LogManager::getSingleton().logMessage("Error loading an entity!");
	}
	element = XMLNode->FirstChildElement("userDataReference");
}

void Level::parseNodes(TiXmlElement *XMLNode)
{
	TiXmlElement *element;

	element = XMLNode->FirstChildElement("node");
	while(element)
	{
		parseLevelObject(element);
		element = element->NextSiblingElement("node");
	}
}