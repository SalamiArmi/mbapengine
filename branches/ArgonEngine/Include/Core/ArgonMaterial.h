#ifndef _ARGONMATERIAL_HEADER_
#define _ARGONMATERIAL_HEADER_

#include <Standard/ArgonPair.h>
#include <Interface/IShader.h>
#include <Interface/IArgonUnknownImp.h>
#include <Interface/IFrameListner.h>

#include "ArgonMesh.h"
#include "ArgonAttribute.h"

namespace Argon
{
	struct MaterialShaderContainer
	{
	public:
		IShader*	m_Shader;
		uint		m_Pass;
		String		m_Technique;
	}; //Struct

	class Material : public IArgonUnknownImp<IFrameListner, GUID_IFrameListner>
	{
	typedef Vector<MaterialShaderContainer>	RenderableShaders;
	typedef Vector<Pair<Mesh*, uint>>		RenderableMeshs;
	typedef Vector<Attribute*>				MaterialAttributes;

	public:
		Material(String Name);
		Material(String Name, const char* FileData);
		~Material();

		///GETNAME(STRING)
		///
		///Get the name of this $Material$
		///
		///No Params:
		String GetName();

		///ADD(VOID)
		///
		///Add a new $Attribute$ to this $Material$, the $Attribute$ is created internally
		///
		///Param Name: The name of the $Attribute$, if the name already exists it will fail to create.
		///Param Type:
		void Add(String Name, AttributeType Type);

		///ADD(VOID)
		///
		///Add a new $Attribute$ to this $Material$.
		///
		///Param Add: The attribute to add, if the $Attribute$ name is already in the list it will not add.
		void Add(Attribute* Add);

		///ADDSHADER(VOID)
		///
		///Add a Shader Resource to the $Material$,
		///
		///Param Name: The Resource name of the shader
		///Param RenderPass: Which pass's does this shader support
		///Param Technique: What Technique to use when Rendering
		void AddShader(String Name, uint RenderPass, String Technique);

		///ADDSHADER(VOID)
		///
		///Add a Shader Resource to the $Material$,
		///
		///Param Name: The Resource name of the shader
		///Param FileData: The Shader data in data format
		///Param RenderPass: Which pass's does this shader support
		///Param Technique: What Technique to use when Rendering
		void AddShader(String Name, const char* FileData, uint RenderPass, String Technique);

		///ADDMESH(VOID)
		///
		///Add a $Mesh$ that will use this $Material$ for a specific Material ID
		///
		///Param Renderable: The $Mesh$ that will be drawn
		///Param MaterialID: The MaterialID that will be rendered
		void AddMesh(Mesh* Renderable, uint MaterialID);

		///REMOVE(VOID)
		///
		///Remove the $Attribute$ with the name
		///
		///Param Name: The name of the $Attribute$
		void Remove(String Name);

		///REMOVE(VOID)
		///
		///Remove an $Attribute$ from this $Material$
		///
		///Param Remove: The $Attribute$ to be removed
		void Remove(Attribute* Remove);

		///REMOVEMESH(VOID)
		///
		///Remove the mesh from being rendered with this $Material$
		///
		///Param Renderable: The $Mesh$ that will be removed 
		///Param MaterialID: The Material ID that will be rendered
		void RemoveMesh(Mesh* Renderable, uint MaterialID);

		///REMOVESHADER(VOID)
		///
		///Remove a shader from this $Material$
		///
		///Param Name: The Shaders Resource name
		void RemoveShader(String Name);

		///REMOVESHADER(VOID)
		///
		///Remove a shader from this $Material$
		///
		///Param Shader: A pointer to the Shader that will be removed 
		void RemoveShader(IShader* Shader);

		///CONTAINS(BOOL)
		///
		///Does this $Material$ contain a specific $Attribute$
		///
		///Param Name: The name of the $Attribute$
		bool Contains(String Name);

		///CONTAINS(BOOL)
		///
		///Does this $Material$ contain a specific $Attribute$
		///
		///Param Contains: A pointer to the $Attribute$ begin checked
		bool Contains(Attribute* Contains);

		///CONTAINSMESH(BOOL)
		///
		///Does this $Material$ contain a specific $Mesh$
		///
		///Param Renderable: The $Mesh$ that will be used as a comparison
		bool ContainsMesh(Mesh* Renderable);

		///CONTAINSSHADER(BOOL)
		///
		///Does this $Material$ contain a specific Shader
		///
		///Param Name: The resouce name of the Shader
		bool ContainsShader(String Name);

		///CONTAINSSHADER(BOOL)
		///
		///Does this $Material$ contain a specific Shader
		///
		///Param Shader: The Shader that will be used as a comparison
		bool ContainsShader(IShader* Shader);

		///SETSHADERTECHNIQUE(VOID)
		///
		///Set a specific detail within the Shader Resource
		///
		///Param Name: The Resource name of the shader
		///Param Technique: What Technique to use when Rendering
		void SetShaderTechnique(String Name, String Technique);

		///SETSHADERRENDERPASS(VOID)
		///
		///Set a specific detail within the Shader Resource
		///
		///Param Name: The Resource name of the shader
		///Param RenderPass: Which pass's does this shader support
		void SetShaderRenderPass(String Name, uint RenderPass);

	private:

		///FRAMEDRAW(BOOL)
		///
		///Draw the Graphical object
		///
		///Param Pass: The pass that will be preformed
		bool FrameDraw(IFrameListner::RenderPass Pass);

		///SUPPORTEDPASS(BOOL)
		///
		///Does the Graphics Support this pass if so make an attempt to render
		///
		///Param Pass: The Pass that will be checked against
		bool SupportsPass(RenderPass Pass);

		String						m_Name;

		MaterialAttributes			m_Attributes;
		RenderableMeshs				m_Meshs;
		RenderableShaders			m_Shaders;
	};
} //Namespace

#endif //_ARGONMATERIAL_HEADER_