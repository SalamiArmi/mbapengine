#pragma once


class PhysicsManager : public singleton<PhysicsManager>
{
	friend singleton;
public:
	void load();
	void unload();

	void update(const float timeDelta);

	void getPlaneDesc(const Ogre::Vector3 normal, const Ogre::Real d, NxPlaneShapeDesc *out) const;

	void createConvexMesh(Ogre::Entity* entity);

	void endUpdate();

	NxActor *addActor(NxActorDesc &);
	NxActor *addActor(NxShapeDesc &);
	NxActor *addActor(const NxShapeDesc& shapeDesc, bool Body);

	void getMeshInformation(Ogre::MeshPtr mesh,size_t &vertex_count, Ogre::Vector3* &vertices, size_t &index_count, unsigned* &indices, const Ogre::Vector3 &position = Ogre::Vector3::ZERO,  const Ogre::Quaternion &orient = Ogre::Quaternion::IDENTITY,const Ogre::Vector3 &scale = Ogre::Vector3::UNIT_SCALE);

	bool loadPhysxCollection(char* fileName);

protected:
	PhysicsManager();
	~PhysicsManager();

private:
	NxPhysicsSDK *mSDK;
	NxScene *mScene;
	NxCookingInterface* m_Cooking;
};