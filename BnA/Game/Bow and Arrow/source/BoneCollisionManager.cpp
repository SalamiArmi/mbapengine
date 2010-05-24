#include "FrameworkPrecompile.h"
#include "BoneCollisionManager.h"
#include <fstream>
#include "UtilFunctions.h"

//Uses ogres singleton template, creates one instances of ParticleManager
template<> BoneCollisionManager* Ogre::Singleton<BoneCollisionManager>::ms_Singleton = 0;

BoneCollisionManager::BoneCollisionManager() : mFile(NULL)
{
}

BoneCollisionManager::~BoneCollisionManager()
{
	fclose(mFile);
}


void BoneCollisionManager::checkMesh(Ogre::String outFileName, Ogre::SceneNode* node)
{
	std::ofstream file(outFileName.c_str());
	if (file)
	{
		Ogre::Entity* ent = (Ogre::Entity*)node->getAttachedObject(0);
		Ogre::SkeletonInstance* skeletonInst = ent->getSkeleton();
		Ogre::Skeleton::BoneIterator boneI=skeletonInst->getBoneIterator();

		//file<<"Creating bone length information from:\n";
		file<<"Mesh name: "<<ent->getMesh()->getName()<<"\n";
		file<<"Skeleton name: "<<skeletonInst->getName()<<"\n\n";

		while(boneI.hasMoreElements())
		{
			Ogre::Bone* bone=boneI.getNext();
			Ogre::String bName=bone->getName();

			if (bone->getChild(0))
			{
				Ogre::Vector3 curr = bone->_getDerivedPosition();
				Ogre::Vector3 next = bone->getChild(0)->_getDerivedPosition();

				Ogre::Vector3 difference = next-curr;

				//length of bone
				Ogre::Real lenght = difference.length();

				file<<bName<<":\nLength\t\t\t=\t"<<Ogre::StringConverter::toString(lenght,3)<<"\n"<<
					"Position"<<"\t\t=\t"<<Ogre::StringConverter::toString(curr.x,1)<<", "<<
					Ogre::StringConverter::toString(curr.y,1)<<", "<<
					Ogre::StringConverter::toString(curr.z,1)<<"\n";
				if (!bone->getParent())
					file<<bName<<" is a Root Bone!\n\n";
				else
					file<<"\n\n";
			}
		}
	}
}

void BoneCollisionManager::CreateBoneData(Ogre::Bone *q, Ogre::String Type, Ogre::Vector3 D, Ogre::String MeshName)
{
	Ogre::String Line;

	if (mFile == NULL)
	{
		mFile = fopen((MeshName.c_str()), "w");
	}

	//Write Top Compoment
	Line = "[" + q->getName() + "]"  + "\n";
	fwrite(Line.c_str(), 1, strlen(Line.c_str()), mFile);

	//Write Bone Name
	Line = "boneName=" + q->getName() + "\n";
	//fputs(Line.c_str(),mFile);
	fwrite(Line.c_str(), 1, strlen(Line.c_str()), mFile);

	//Write Type
	Line = "actorShape="+Type+"\n";
	//fputs(Line.c_str(),mFile);
	fwrite(Line.c_str(), 1, strlen(Line.c_str()), mFile);

	//Write Dimensions
	std::stringstream s;
	std::stringstream ss;
	std::stringstream sss;
	s << D.x;
	ss << D.y;
	sss << D.z;
	Line = "dimensions=";
	Line += s.str()+" "+ss.str()+" "+sss.str()+"\n"+"\n";
	fputs(Line.c_str(),mFile);
	
	fflush(mFile);
}

BoneCollisionManager* BoneCollisionManager::getSingletonPtr()
{
	return ms_Singleton;
}

BoneCollisionManager& BoneCollisionManager::getSingleton()
{  
	assert( ms_Singleton );  return ( *ms_Singleton );  
}

std::vector<::NxOgre::KinematicActor*> &BoneCollisionManager::getBoneCollisions()
{
	return mBoneCollisions;
}