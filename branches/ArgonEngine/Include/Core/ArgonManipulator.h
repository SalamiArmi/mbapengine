#ifndef _ARGONMINIPULATOR_HEADER_
#define _ARGONMINIPULATOR_HEADER_

namespace Argon
{
	class Entity;

	class Manipulator
	{
	public:
		Manipulator(Entity* SceneNode);
		~Manipulator();

		///GETATTACHEDENTITY(ENTITY)
		///
		/// Get the attached entity which is being manipulated
		///
		///No Params:
		Entity* GetAttachedEntity();

		///PREPROCESS(BOOL)
		///
		/// Process any data Pre rendering
		///
		///No Params:
		bool PreProcess();

		///POSTPROCESS(BOOL)
		///
		/// Process any data Post rendering
		///
		///No Params:
		bool PostProcess();

		///GETENABLED(BOOL)
		///
		/// Get if the Manipulator is will change the state of the attched $Entity$
		///
		///No Params:
		bool GetEnabled();

		///SETENABLED(VOID)
		///
		/// Set if the Manipulator is will change the state of the attched $Entity$
		///
		///No Params:
		void SetEnabled(bool Enabled);

	private:
		Entity*	m_Entity;
		bool	m_Enabled;
	}; //Class

} //Namespace

#endif //_ARGONMINIPULATOR_HEADER_