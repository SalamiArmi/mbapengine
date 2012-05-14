#include "ArgonMaterial.h"
#include "ArgonRoot.h"

namespace Argon
{
	Material::Material(String Name)
		: m_Name(Name)
	{
	}

	Material::Material(String Name, const char* FileData)
		: m_Name(Name)
	{
		//Read from file
	}

	Material::~Material()
	{
	}

	String Material::GetName()
	{
		return m_Name;
	}

	void Material::Add(String Name, AttributeType Type)
	{
		m_Attributes.Push_Back(new Attribute(Name, Type));
	}

	void Material::Add(Attribute* Add)
	{
		for(MaterialAttributes::Iterator AttributeIterator = m_Attributes.Begin(); AttributeIterator != m_Attributes.End(); ++AttributeIterator)
		{
			if((*AttributeIterator)->GetName() == Add->GetName())
			{
				return;
			}
		}
		
		m_Attributes.Push_Back(Add);
	}

	void Material::AddShader(String Name, uint RenderPass, String Technique)
	{

	}

	void Material::AddShader(String Name, const char* FileData, uint RenderPass, String Technique)
	{
		IShader* Shader = Root::instance()->GetActiveRenderSystem()->CreateShader(Name, FileData);
		ArgonAssert(Shader);

		if(Shader)
		{
			m_Shaders.Push_Back(MaterialShaderContainer());
			m_Shaders.Back().m_Shader = Shader;
			m_Shaders.Back().m_Pass = RenderPass;
			m_Shaders.Back().m_Technique = Technique;

			uint Index = 0;
			String VariableName = "";
			
			while(Shader->GetVariableName(Index, VariableName))
			{
				IShader::VariableType Type = Shader->GetVariableType(VariableName);
				ArgonAssert(Type != IShader::TYPE_Unknown);

				Attribute* NewAttribute = NULL;

				switch(Type)
				{
					case IShader::TYPE_Bool:
					{
						NewAttribute = new Attribute(VariableName, ATTRIBUTETYPE_Bool);
						break;
					}
					case IShader::TYPE_Integer:
					{
						NewAttribute = new Attribute(VariableName, ATTRIBUTETYPE_Integer);
						break;
					}
					case IShader::TYPE_Float:
					{
						NewAttribute = new Attribute(VariableName, ATTRIBUTETYPE_Float);
						break;
					}
					case IShader::TYPE_String:
					{
						NewAttribute = new Attribute(VariableName, ATTRIBUTETYPE_String);
						break;
					}
					case IShader::TYPE_Vector2:
					{
						NewAttribute = new Attribute(VariableName, ATTRIBUTETYPE_Vector2);
						break;
					}
					case IShader::TYPE_Vector3:
					{
						NewAttribute = new Attribute(VariableName, ATTRIBUTETYPE_Vector3);
						break;
					}
					case IShader::TYPE_Vector4:
					{
						NewAttribute = new Attribute(VariableName, ATTRIBUTETYPE_Vector4);
						break;
					}
					case IShader::TYPE_Matrix3:
					{
						NewAttribute = new Attribute(VariableName, ATTRIBUTETYPE_Matrix3);
						break;
					}
					case IShader::TYPE_Matrix4:
					{
						NewAttribute = new Attribute(VariableName, ATTRIBUTETYPE_Matrix4);
						break;
					}
				}

				if(NewAttribute)
				{
					m_Attributes.Push_Back(NewAttribute);
				}
			}
		}
	}

	void Material::AddMesh(Mesh* Renderable, uint MaterialID)
	{
		for(RenderableMeshs::Iterator MeshIterator = m_Meshs.Begin(); MeshIterator != m_Meshs.End(); ++MeshIterator)
		{
			if((*MeshIterator).First == Renderable && (*MeshIterator).Second == MaterialID)
			{
				return;
			}
		}

		m_Meshs.Push_Back(MakePair(Renderable, MaterialID));
	}

	void Material::Remove(String Name)
	{
		for(MaterialAttributes::Iterator AttributeIterator = m_Attributes.Begin(); AttributeIterator != m_Attributes.End(); ++AttributeIterator)
		{
			if((*AttributeIterator)->GetName() == Name)
			{
				m_Attributes.Erase(AttributeIterator);
			}
		}
	}

	void Material::Remove(Attribute* Remove)
	{
		for(MaterialAttributes::Iterator AttributeIterator = m_Attributes.Begin(); AttributeIterator != m_Attributes.End(); ++AttributeIterator)
		{
			if((*AttributeIterator) == Remove)
			{
				m_Attributes.Erase(AttributeIterator);
			}
		}
	}

	void Material::RemoveMesh(Mesh* Renderable, uint MaterialID)
	{
		for(RenderableMeshs::Iterator MeshIterator = m_Meshs.Begin(); MeshIterator != m_Meshs.End(); ++MeshIterator)
		{
			if((*MeshIterator).First == Renderable && (*MeshIterator).Second == MaterialID)
			{
				m_Meshs.Erase(MeshIterator);
			}
		}
	}

	void Material::RemoveShader(String Name)
	{
		for(RenderableShaders::Iterator ShaderIterator = m_Shaders.Begin(); ShaderIterator != m_Shaders.End(); ++ShaderIterator)
		{
			if((*ShaderIterator).m_Shader->GetName() == Name)
			{
				m_Shaders.Erase(ShaderIterator);
			}
		}
	}

	void Material::RemoveShader(IShader* Shader)
	{
		for(RenderableShaders::Iterator ShaderIterator = m_Shaders.Begin(); ShaderIterator != m_Shaders.End(); ++ShaderIterator)
		{
			if((*ShaderIterator).m_Shader == Shader)
			{
				m_Shaders.Erase(ShaderIterator);
			}
		}
	}

	bool Material::Contains(String Name)
	{
		for(MaterialAttributes::Iterator AttributeIterator = m_Attributes.Begin(); AttributeIterator != m_Attributes.End(); ++AttributeIterator)
		{
			if((*AttributeIterator)->GetName() == Name)
			{
				return true;
			}
		}
		return false;
	}

	bool Material::Contains(Attribute* Contains)
	{
		for(MaterialAttributes::Iterator AttributeIterator = m_Attributes.Begin(); AttributeIterator != m_Attributes.End(); ++AttributeIterator)
		{
			if((*AttributeIterator) == Contains)
			{
				return true;
			}
		}
		return false;
	}

	bool Material::ContainsMesh(Mesh* Renderable)
	{
		for(RenderableMeshs::Iterator MeshIterator = m_Meshs.Begin(); MeshIterator != m_Meshs.End(); ++MeshIterator)
		{
			if((*MeshIterator).First == Renderable)
			{
				return true;
			}
		}
		return false;
	}

	bool Material::ContainsShader(String Name)
	{
		for(RenderableMeshs::Iterator MeshIterator = m_Meshs.Begin(); MeshIterator != m_Meshs.End(); ++MeshIterator)
		{
			//TODO
		}

		return false;
	}

	bool Material::ContainsShader(IShader* Shader)
	{
		for(RenderableShaders::Iterator ShaderIterator = m_Shaders.Begin(); ShaderIterator != m_Shaders.End(); ++ShaderIterator)
		{
			if((*ShaderIterator).m_Shader == Shader)
			{
				return true;
			}
		}

		return false;
	}

	void Material::SetShaderTechnique(String Name, String Technique)
	{
		for(RenderableShaders::Iterator ShaderIterator = m_Shaders.Begin(); ShaderIterator != m_Shaders.End(); ++ShaderIterator)
		{
			if((*ShaderIterator).m_Shader->GetName() == Name)
			{
				(*ShaderIterator).m_Technique = Technique;
			}
		}
	}
	
	void Material::SetShaderRenderPass(String Name, uint RenderPass)
	{
		for(RenderableShaders::Iterator ShaderIterator = m_Shaders.Begin(); ShaderIterator != m_Shaders.End(); ++ShaderIterator)
		{
			if((*ShaderIterator).m_Shader->GetName() == Name)
			{
				(*ShaderIterator).m_Pass = RenderPass;
			}
		}
	}

	bool Material::FrameDraw(IFrameListner::RenderPass Pass)
	{
		if(m_Shaders.Size() > 0 && m_Meshs.Size() > 0 && m_Attributes.Size() > 0)
		{
			bool Success = true;
			for(RenderableShaders::Iterator ShaderIterator = m_Shaders.Begin(); ShaderIterator != m_Shaders.End(); ++ShaderIterator)
			{
				if((*ShaderIterator).m_Pass & Pass) //Does a single shader support this pass
				{
					(*ShaderIterator).m_Shader->SetTechnique((*ShaderIterator).m_Technique);

					//Set all values here
					for(Vector<Attribute*>::Iterator AttributeIterator = m_Attributes.Begin(); AttributeIterator != m_Attributes.End(); ++AttributeIterator)
					{			
						switch(((AttributeType)(*AttributeIterator)->GetType()))
						{
							case ATTRIBUTETYPE_Float:
							{
								(*ShaderIterator).m_Shader->SetFloat((*AttributeIterator)->GetName(), (*AttributeIterator)->GetAsFloat());
								break;
							}
							case ATTRIBUTETYPE_Integer:
							{
								(*ShaderIterator).m_Shader->SetInteger((*AttributeIterator)->GetName(), (*AttributeIterator)->GetAsInteger());
								break;
							}
						}
					}	

					//Bind the Shader
					if((*ShaderIterator).m_Shader->Bind(Pass))
					{
						//Attempt to Draw all Mesh's
						for(RenderableMeshs::Iterator MeshIterator = m_Meshs.Begin(); MeshIterator != m_Meshs.End(); ++MeshIterator)
						{
							ArgonAssert((*MeshIterator).First->Bind());

							//Draw the Mesh ID
							ArgonAssert((*MeshIterator).First->Draw((*MeshIterator).Second)); 

							ArgonAssert((*MeshIterator).First->UnBind());
						}

						//Unbind the shader all drawing is complete
						(*ShaderIterator).m_Shader->UnBind();

						Success &= true;
					}
					else Success &= false;
				}
			}
		}
		return false;
	}

	bool Material::SupportsPass(RenderPass Pass)
	{
		if(m_Shaders.Size() > 0)
		{
			for(RenderableShaders::Iterator it = m_Shaders.Begin(); it != m_Shaders.End(); ++it)
			{
				if((*it).m_Pass & Pass) //Does a single shader support this pass
				{
					return true;
				}
			}
		}

		return false;
	}

} //Namespace