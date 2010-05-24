//////////////////////////////////////////////////////////////////////////
//_BONECOLLISIONMANAGER_HEADER_
//
//Created By: Mitchel Box
//
//28/9/9
//
//Bone Collision Manager handles the creation of all output files and the 
//creation of CheckMesh file.
//Bone Collision Manager is a singleton and is to be created once.
//
//@Brief Description
//checkMesh(VOID)
//outputs a diagnostic file checking length of bones.
//
//@Brief Description
//Creates the necessary Bone information for making the bone collision
//work correctly
//////////////////////////////////////////////////////////////////////////
#ifndef _BONECOLLISIONMANAGER_HEADER_
#define _BONECOLLISIONMANAGER_HEADER_

class BoneCollision;

namespace Ogre
{
	class SceneManager;
	class Skeleton;
	class SkeletonManager;
	class SkeletonPtr;
}

class BoneCollisionManager : public Ogre::Singleton<BoneCollisionManager>
{
public:
	BoneCollisionManager();

	~BoneCollisionManager();

	//outputs a diagnostic file checking length of bones.
	void										checkMesh(Ogre::String outFileName, Ogre::SceneNode *node);

	//Creates the necessary Bone information for making the bone collision work correctly
	void										CreateBoneData(Ogre::Bone *q, Ogre::String Type, Ogre::Vector3 D, Ogre::String MeshName);

	//Singletons
	static BoneCollisionManager&				getSingleton();
	static BoneCollisionManager*				getSingletonPtr();

	std::vector<::NxOgre::KinematicActor*>		&getBoneCollisions();

protected:
	std::vector<::NxOgre::KinematicActor*>		mBoneCollisions;

	FILE *mFile;
};

#endif //_BONECOLLISIONMANAGER_HEADER_