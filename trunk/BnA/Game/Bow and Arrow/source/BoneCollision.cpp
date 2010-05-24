#include "FrameworkPrecompile.h"
#include "BoneCollision.h"
#include "BoneCollisionManager.h"
#include "UtilFunctions.h"
#include "WorldState.h"

BoneCollision::BoneCollision(OGRE3DRenderSystem* Render, Ogre::String FileName, Ogre::SceneNode *node, bool initBoneFile, Ogre::Real bodyDensity) :
mBonesCounter(0),
mBodyDensity(985),
mRender(Render),
mNode(node),
mFileName(FileName)
{
	if (initBoneFile)
	{
		mFileReader.loadFromResourceSystem(FileName, "General");

		Ogre::ConfigFile::SectionIterator it = mFileReader.getSectionIterator();

		Ogre::String secName, paramName, valueName;

		while (it.hasMoreElements())
		{
			secName = it.peekNextKey();

			Ogre::ConfigFile::SettingsMultiMap *settings = it.getNext();
			Ogre::ConfigFile::SettingsMultiMap::iterator i;

			std::map<Ogre::String, Ogre::String> sectionData;

			for (i = settings->begin(); i != settings->end(); ++i)
			{
				paramName = i->first;
				valueName = i->second;

				sectionData[paramName]=valueName;
			}
			if (secName != "")
				parseSectionData(secName, sectionData);
		}
	}
}

BoneCollision::~BoneCollision()
{
	for (int i = 0; i < mInformation.size(); ++i)
	{
		mInformation[i].mBoneActor->setGlobalPosition(NxOgre::Real3(0,0,0));
	}

	for (int i = 0; i < mCollisionOjects.size(); ++i)
	{
		mCollisionOjects[i]->setGlobalPosition(NxOgre::Real3(0,0,0));
	}
}

void BoneCollision::parseSectionData(Ogre::String secName, std::map<Ogre::String,Ogre::String> section)
{
	Ogre::Entity* ent = (Ogre::Entity*)mNode->getAttachedObject(0);

	mBoneActorBind[mBonesCounter].mName = secName;
	mBoneActorBind[mBonesCounter].mBone = ent->getSkeleton()->getBone(section["boneName"]);

	if (section["actorShape"]==Ogre::String("sphere"))
	{
		Ogre::Real dimensions = Ogre::StringConverter::parseReal(section["dimensions"]);

		mBoneActorBind[mBonesCounter].mBoneActor = mRender->getScene()->createKinematicActor(new NxOgre::Sphere(dimensions));
		mBoneActorBind[mBonesCounter].mBoneActor->getNxActor()->setContactReportFlags(NX_NOTIFY_ALL);

		mBoneActorBind[mBonesCounter].mFlags = eBoneCollisionFlags::BoneAlive;
		mInformation.push_back(mBoneActorBind[mBonesCounter]);
	}
	else if (section["actorShape"]==Ogre::String("capsule"))
	{
		Ogre::Vector2 dimensions = Ogre::StringConverter::parseVector2(section["dimensions"]);

		NxOgre::Real3 GlobalPosition; NxOgre::Matrix33 GlobalOrentation;
		ConvertVector3(ent->getSkeleton()->getBone(section["boneName"])->_getDerivedPosition(), GlobalPosition);
		ConvertQuaternion(ent->getSkeleton()->getBone(section["boneName"])->_getDerivedOrientation(), GlobalOrentation.extractQuaternion());

		mBoneActorBind[mBonesCounter].mBoneActor =  mRender->getScene()->createKinematicActor(new NxOgre::Capsule(dimensions.x, dimensions.y));
		mBoneActorBind[mBonesCounter].mBoneActor->setGlobalPosition(GlobalPosition);
		mBoneActorBind[mBonesCounter].mBoneActor->setGlobalOrientation(GlobalOrentation);
		mBoneActorBind[mBonesCounter].mName = section["boneName"];

		mBoneActorBind[mBonesCounter].mBoneActor->getNxActor()->userData = (void*)mBoneActorBind[mBonesCounter].mBoneActor;
		mBoneActorBind[mBonesCounter].mBoneActor->getNxActor()->setContactReportFlags(NX_NOTIFY_ALL);
		mBoneActorBind[mBonesCounter].mFlags = eBoneCollisionFlags::BoneAlive;

		mCollisionOjects.push_back(mBoneActorBind[mBonesCounter].mBoneActor);

		mBoneActorBind[mBonesCounter].mFlags = eBoneCollisionFlags::BoneAlive;
		mInformation.push_back(mBoneActorBind[mBonesCounter]);
	}
	else if (section["actorShape"]==Ogre::String("box"))
	{
		Ogre::Vector3 dimensions = Ogre::StringConverter::parseVector3(section["dimensions"]);
		NxOgre::Real3 GlobalPosition; NxOgre::Matrix33 GlobalOrentation;
		ConvertVector3(ent->getSkeleton()->getBone(section["boneName"])->_getDerivedPosition(), GlobalPosition);
		ConvertQuaternion(ent->getSkeleton()->getBone(section["boneName"])->_getDerivedOrientation(), GlobalOrentation.extractQuaternion());

		mBoneActorBind[mBonesCounter].mBoneActor =  mRender->getScene()->createKinematicActor(new NxOgre::Box(dimensions.x, dimensions.y,dimensions.z));
		mBoneActorBind[mBonesCounter].mBoneActor->setGlobalPosition(GlobalPosition);
		mBoneActorBind[mBonesCounter].mBoneActor->setGlobalOrientation(GlobalOrentation);
		mBoneActorBind[mBonesCounter].mName = section["boneName"];

		mBoneActorBind[mBonesCounter].mBoneActor->getNxActor()->userData = (void*)mBoneActorBind[mBonesCounter].mBoneActor;
		mBoneActorBind[mBonesCounter].mBoneActor->getNxActor()->setContactReportFlags(NX_NOTIFY_ALL);

		//Create the blood particles for the actor position
		mBoneActorBind[mBonesCounter].mBloodParticleSystem = WorldState::getSingleton().getSceneMgr()->createParticleSystem(mBoneActorBind[mBonesCounter].mName + "Particle" + Ogre::StringConverter::toString(WorldState::getSingleton().getParticleCount()), "EnemyBlood");
		mBoneActorBind[mBonesCounter].mBloodParticleSystem->getEmitter(0)->setEmissionRate(0);

		mCollisionOjects.push_back(mBoneActorBind[mBonesCounter].mBoneActor);

		mBoneActorBind[mBonesCounter].mFlags = eBoneCollisionFlags::BoneAlive;
		mInformation.push_back(mBoneActorBind[mBonesCounter]);
	}

	//he have found a root bone - use it for character positioning
	if (!mBoneActorBind[mBonesCounter].mBone->getParent())
		mPositionControllingBone = &mBoneActorBind[mBonesCounter];

	BoneCollisionManager::getSingleton().getBoneCollisions().push_back(mBoneActorBind[mBonesCounter].mBoneActor);

	mBonesCounter++;
}

void BoneCollision::setupBoneCollision(Ogre::Entity* ENT, Ogre::String actor_type)
{
	Ogre::Skeleton::BoneIterator it = ENT->getSkeleton()->getBoneIterator();

	while(it.hasMoreElements())
	{
		Ogre::Bone *B = it.getNext();
		Ogre::Node *P = B->getParent();

		NxOgre::Real3 GlobalPosition; NxOgre::Matrix33 GlobalOrentation;
		ConvertVector3(B->_getDerivedPosition(), GlobalPosition);
		ConvertQuaternion(B->_getDerivedOrientation(), GlobalOrentation.extractQuaternion());

		if (P != NULL)
		{
			Ogre::Real lengthBetweenBones = (B->_getDerivedPosition() - P->_getDerivedPosition()).length();
			if (actor_type == "capsule")
			{
				::NxOgre::KinematicActor *temp = mRender->getScene()->createKinematicActor(new NxOgre::Capsule(NxOgre::Real(0.1f), lengthBetweenBones));

				temp->setGlobalPosition(GlobalPosition);
				temp->setGlobalOrientation(GlobalOrentation);

				BoneCollisionManager::getSingleton().CreateBoneData(B, actor_type, Ogre::Vector3(lengthBetweenBones, 0.1f,0), mFileName);
			}
			else if(actor_type == "box")
			{
				::NxOgre::KinematicActor *temp = mRender->getScene()->createKinematicActor(new NxOgre::Box(lengthBetweenBones, mNode->getScale().z, mNode->getScale().y/10));

				temp->setGlobalPosition(GlobalPosition);
				temp->setGlobalOrientation(GlobalOrentation);

				BoneCollisionManager::getSingleton().CreateBoneData(B, actor_type, Ogre::Vector3(lengthBetweenBones, mNode->getScale().z, mNode->getScale().y/10), mFileName);
			}
		}
	}
}

void BoneCollision::update()
{
	std::vector<BoneActorBind>::iterator it;

	for (it = mInformation.begin(); it != mInformation.end(); it++)
	{
		//Set the new position using
		//NodePos + NodeOrentation * (BoneDerievedPos * NodeScale); 
		Ogre::Entity* e = (Ogre::Entity*)mNode->getAttachedObject(0);

		NxOgre::Real3 nxTruePos;

		Ogre::Vector3 ogreTruePos = mNode->getPosition() + mNode->getOrientation() * (e->getSkeleton()->getBone((*it).mName)->_getDerivedPosition() * mNode->getScale());

		ConvertVector3(ogreTruePos, nxTruePos);

		(*it).mBoneActor->setGlobalPosition(nxTruePos);	

		NxOgre::Real4 rotation;
		ConvertQuaternion(e->getSkeleton()->getBone((*it).mName)->_getDerivedOrientation(), rotation);
		(*it).mBoneActor->setGlobalOrientationQuat(rotation);
	}
}

void BoneCollision::addJoints()
{

}
