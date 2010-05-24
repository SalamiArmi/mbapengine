#include "Precompiled.h"
#include "PhysicsManager.h"
#include "NxRemoteDebugger.h"

using namespace Ogre;

PhysicsManager::PhysicsManager()
:
mSDK(0),
mScene(0)
{
	load();
	m_Cooking = NxGetCookingLib(NX_PHYSICS_SDK_VERSION);
	if ( NxInitCooking() == false )
		Ogre::LogManager::getSingleton().logMessage("Failed To start Cooking");
}

PhysicsManager::~PhysicsManager()
{
	unload();
}

void PhysicsManager::load()
{
	// Initialize PhysicsSDK
	NxPhysicsSDKDesc aSDKDesc;
	NxSDKCreateError errorCode = NXCE_NO_ERROR;
	mSDK  = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, 0, 0, aSDKDesc, &errorCode);
	if(mSDK == NULL) 
	{
		Ogre::LogManager::getSingleton().logMessage("Unable to initialize the PhysX SDK");
	}


	if (mSDK->getFoundationSDK().getRemoteDebugger())
	{
		mSDK->getFoundationSDK().getRemoteDebugger()->connect( "localhost", NX_DBG_DEFAULT_PORT, NX_DBG_EVENTMASK_EVERYTHING );
		mSDK->setParameter(NX_SKIN_WIDTH, 0.05f);
		Ogre::LogManager::getSingleton().logMessage("SDK Connected to debugger");
	}


	// Create a physics scene
	NxSceneDesc aSceneDesc;
	aSceneDesc.gravity = NxVec3(0.0f, 9.8f, 0.0f);
	mScene = mSDK->createScene(aSceneDesc);
	// Log error if fails & quit
	if (mScene == 0)
	{
		return;
	}

}

void PhysicsManager::unload()
{
	// Release the scene before the SDK
	if (mScene != 0)
	{
		mSDK->releaseScene(*mScene);
		mScene = 0;
	}

	// Release the SDK last
	if (mSDK != 0)
	{
		NxReleasePhysicsSDK(mSDK);
		mSDK = 0;
	}
}

void PhysicsManager::update(const float timeDelta)
{
	mScene->simulate(timeDelta);
	mScene->flushStream();

}

void PhysicsManager::endUpdate()
{
	mScene->fetchResults(NX_ALL_FINISHED);
}

void PhysicsManager::getPlaneDesc(const Ogre::Vector3 normal, const Ogre::Real  d, NxPlaneShapeDesc *out) const
{
	out->normal = NxVec3(normal.x, normal.y, normal.z);
	out->d = d;
}

NxActor *PhysicsManager::addActor(NxActorDesc &desc)
{
	// Is the actor description valid?
	if (!desc.isValid())
	{
		// Nope, lets get out of here
		return 0;
	}

	// Otherwise, lets return our new actor
	return mScene->createActor(desc);
}

NxActor *PhysicsManager::addActor(NxShapeDesc &desc)
{
	// Is the shape description valid?
	if (!desc.isValid())
	{
		// Nope, lets get out of here
		return 0;
	}

	NxActorDesc t_actorDesc;
	t_actorDesc.shapes.push_back(&desc);

	// Otherwise, lets return our new actor
	return addActor(t_actorDesc);
}

void PhysicsManager::createConvexMesh(Ogre::Entity* entity)
{
	bool added_shared = false;
	size_t current_offset = 0;
	size_t shared_offset = 0;
	size_t next_offset = 0;
	size_t index_offset = 0;

	size_t vertex_count, index_count;
	Ogre::Vector3 *VertexData;
	unsigned int *indecies;
#if USE_THIS_IT_SHOULD_WORK
	getMeshInformation(entity->getMesh(), vertex_count, *&VertexData, index_count,indecies);

	NxTriangleMeshDesc TriMeshDesc;
	TriMeshDesc.numVertices = vertex_count;  
	TriMeshDesc.numTriangles = index_count / 3; 
	TriMeshDesc.pointStrideBytes = sizeof(Ogre::Vector3); 
	TriMeshDesc.triangleStrideBytes = 3*sizeof(float); 
	TriMeshDesc.points = VertexData;  
	TriMeshDesc.triangles = (void*)indecies; 
	TriMeshDesc.flags = NX_MF_16_BIT_INDICES;
	TriMeshDesc.heightFieldVerticalAxis = NX_Z;
	TriMeshDesc.heightFieldVerticalExtent = -1000;


	NxTriangleMeshShapeDesc TriMeshShapeDesc;
	NxTriangleMesh* TriMesh;

	//m_Cooking->NxCookTriangleMesh(TriMeshDesc, UserStream("../../Media/cooked.bin", false));
	//TriMesh =  mSDK->createTriangleMesh(UserStream("../../Media/cooked.bin", true));



	MemoryWriteBuffer stream;
	if ( m_Cooking->NxCookTriangleMesh( TriMeshDesc, stream ) )
	{
		MemoryReadBuffer readBuffer(stream.data);
		TriMeshShapeDesc.meshData = mSDK->createTriangleMesh(readBuffer);
	}
	else
	{
		Ogre::LogManager::getSingleton().logMessage("Failed meshShape cooking for Entity '" + entity->getName() + "'.");
	}



	//TriMesh.flags |= NX_MF_FLIPNORMALS;

	//if(TriMesh)
	//NxActor *newActor = addActor(TriMeshDesc);
#endif
}

NxActor* PhysicsManager::addActor(const NxShapeDesc& shapeDesc, bool Body = true)
{
	if (!mScene) return NULL;
	NxBodyDesc bodyDesc;
	NxActorDesc actorDesc;

	NxSphereShapeDesc sphereDesc;
	sphereDesc.localPose.t.x = 1;
	sphereDesc.radius = 1;
	sphereDesc.shapeFlags = NX_SF_VISUALIZATION | NX_TRIGGER_ENABLE;

	actorDesc.shapes.pushBack(&(NxShapeDesc&)shapeDesc);

	if (Body)
	{
		bodyDesc.angularDamping	= 0.5f;
		actorDesc.body			= &bodyDesc;
		actorDesc.density		= 10.0f;
	}
	return mScene->createActor(actorDesc);
}


void PhysicsManager::getMeshInformation(Ogre::MeshPtr mesh,size_t &vertex_count,Vector3* &vertices, size_t &index_count, unsigned* &indices, const Ogre::Vector3 &position,  const Ogre::Quaternion &orient,const Ogre::Vector3 &scale)
{
	vertex_count = index_count = 0;

	bool added_shared = false;
	size_t current_offset = vertex_count;
	size_t shared_offset = vertex_count;
	size_t next_offset = vertex_count;
	size_t index_offset = index_count;
	size_t prev_vert = vertex_count;
	size_t prev_ind = index_count;

	// Calculate how many vertices and indices we're going to need
	for(int i = 0;i < mesh->getNumSubMeshes();i++)
	{
		SubMesh* submesh = mesh->getSubMesh(i);

		// We only need to add the shared vertices once
		if(submesh->useSharedVertices)
		{
			if(!added_shared)
			{
				VertexData* vertex_data = mesh->sharedVertexData;
				vertex_count += vertex_data->vertexCount;
				added_shared = true;
			}
		}
		else
		{
			VertexData* vertex_data = submesh->vertexData;
			vertex_count += vertex_data->vertexCount;
		}

		// Add the indices
		Ogre::IndexData* index_data = submesh->indexData;
		index_count += index_data->indexCount;
	}

	// Allocate space for the vertices and indices
	vertices = new Vector3[vertex_count];
	indices = new unsigned[index_count];

	added_shared = false;

	// Run through the submeshes again, adding the data into the arrays
	for(int i = 0;i < mesh->getNumSubMeshes();i++)
	{
		SubMesh* submesh = mesh->getSubMesh(i);

		Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;
		if((!submesh->useSharedVertices)||(submesh->useSharedVertices && !added_shared))
		{
			if(submesh->useSharedVertices)
			{
				added_shared = true;
				shared_offset = current_offset;
			}

			const Ogre::VertexElement* posElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
			Ogre::HardwareVertexBufferSharedPtr vbuf = vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());
			unsigned char* vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
			Ogre::Real* pReal;

			for(size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
			{
				posElem->baseVertexPointerToElement(vertex, &pReal);

				Vector3 pt;

				pt.x = (*pReal++);
				pt.y = (*pReal++);
				pt.z = (*pReal++);

				pt = (orient * (pt * scale)) + position;

				vertices[current_offset + j].x = pt.x;
				vertices[current_offset + j].y = pt.y;
				vertices[current_offset + j].z = pt.z;
			}
			vbuf->unlock();
			next_offset += vertex_data->vertexCount;
		}

		Ogre::IndexData* index_data = submesh->indexData;

		size_t numTris = index_data->indexCount / 3;
		unsigned short* pShort;
		unsigned int* pInt;
		Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
		bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);
		if (use32bitindexes) pInt = static_cast<unsigned int*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		else pShort = static_cast<unsigned short*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

		for(size_t k = 0; k < numTris; ++k)
		{
			size_t offset = (submesh->useSharedVertices)?shared_offset:current_offset;

			unsigned int vindex = use32bitindexes? *pInt++ : *pShort++;
			indices[index_offset + 0] = vindex + offset;
			vindex = use32bitindexes? *pInt++ : *pShort++;
			indices[index_offset + 1] = vindex + offset;
			vindex = use32bitindexes? *pInt++ : *pShort++;
			indices[index_offset + 2] = vindex + offset;

			index_offset += 3;
		}
		ibuf->unlock();
		current_offset = next_offset;
	}
}


bool PhysicsManager::loadPhysxCollection( char *fileName )
{
	bool success = false;

	if ( mSDK )
	{

		//Only load xml files for now
		NXU::NxuPhysicsCollection *PhysicsCollection = NXU::loadCollection( fileName, NXU::NXU_FileType::FT_XML );

		if ( PhysicsCollection )
		{

			if ( mSDK )
			{
				success = NXU::instantiateCollection( PhysicsCollection, *mSDK, 0, 0, 0 );
			}
			NXU::releaseCollection( PhysicsCollection );
		}
		else
		{
		}
	}

	if ( success )
	{
		Ogre::LogManager::getSingleton().logMessage("Physcis Scene loaded from file");
	}

	return success;
}