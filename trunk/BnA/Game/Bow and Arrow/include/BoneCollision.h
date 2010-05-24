////////////////////////////////////////////////////////////////////////////
//BONECOLLISION_HEADER
//
//Created by: Mitchel Box
//
//BoneCollision is used to create kenimatic objects around the mesh object for
//hit box detection. The kenimatic object type is readin by file using the Ogre
//config file class.
//Once they are readin the function addJoints will be called with the information
//needed to create the desired outline. If no collision file already exsists use
//the BoneCollisionManager to create the desired Collision file needed to proceed.
//
//BoneCollisionManager is a singleton.
//
//When the BoneCollision is deleted it automaitcly update the file if needed
////////////////////////////////////////////////////////////////////////////


#ifndef _BONECOLLISION_HEADER_
#define _BONECOLLISION_HEADER_

enum eBoneCollisionFlags
{
	BoneHit, //The Bone is being hit at the current Time
	BoneDead, //The current bone or capsuale is dead and shall not be hit again
	BoneAlive //the current Bone is active and needs to be hit
};

struct BoneActorBind
{
	::Ogre::Bone*				mBone;
	::NxOgre::KinematicActor*	mBoneActor;

	::Ogre::String				mName;
	::Ogre::SceneNode*			mNode;

	eBoneCollisionFlags			mFlags;

	Ogre::ParticleSystem*		mBloodParticleSystem;
};

class BoneCollision
{
public:
	//If no Collision has been made prior to 
	//wanting to load a Mesh with bone collision access the BoneCollision Manager and access
	//the singleton to create nessacry information
	BoneCollision(OGRE3DRenderSystem* Render, Ogre::String FileName, Ogre::SceneNode *node, bool initBoneFile = true,Ogre::Real bodyDensity = 985);
	~BoneCollision();
	//Bones from skeleton/amimation have control over boneActors
	void									setControlToBone();

	//Add new joints
	void									addJoints();

	//SetUpBoneCollision(VOID)
	//This function sets ups and adds all actors to the actor Vector
	void									setupBoneCollision(Ogre::Entity* ENT, Ogre::String actor_type);

	Ogre::SceneNode*						getNode() {return mNode;}

	void									update();

	//Retirve all Bone collisions
	std::vector<::NxOgre::KinematicActor*>	&getBoneCollisions() {return mCollisionOjects;}

	//return the information about the bone that capusale is being created for and and entire 
	//nxactor
	std::vector<BoneActorBind> &getBonesAndCapsule() {return mInformation;}

protected:

	void									parseSectionData(Ogre::String secName, std::map<Ogre::String, Ogre::String> section);

	Ogre::Real								mBodyDensity;
	
	Ogre::SceneNode*						mNode;

	Ogre::ConfigFile						mFileReader;

	int										mBonesCounter;

	std::vector<BoneActorBind>				mInformation;

	std::vector<::NxOgre::KinematicActor*>	mCollisionOjects;

	BoneActorBind							mBoneActorBind[128];

	BoneActorBind							*mPositionControllingBone;

	OGRE3DRenderSystem*						mRender;

	Ogre::String							mFileName;

};

#endif //_BONECOLLISION_HEADER_