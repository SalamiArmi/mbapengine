#ifndef _MESH_HEADER_
#define _MESH_HEADER_

#include "Pair.h"
#include <string>

namespace OOS
{
	class Mesh
	{
	public:
		Mesh();
		virtual ~Mesh();

		virtual bool loadMesh(std::string fileName) { return false; }
				
		virtual void releaseMesh();

	protected:

		/*Pair<D3DMATERIAL9, LPDIRECT3DTEXTURE9> m_Materials;

		DWORD m_Segments;
		
		LPD3DXBUFFER m_AdjcentsBuffer;
		LPD3DXBUFFER m_MaterialBuffer;
		LPD3DXBUFFER m_EffectBuffer;*/
	};

}

#endif //_MESH_HEADER_