import javax.media.j3d.BranchGroup;


public class ArgonJ3DSceneManager 
{
	public ArgonJ3DSceneManager(String Name, ArgonJ3DDevice Creator)
	{
		//Members
		m_SceneGraph = new BranchGroup();
		m_Creator = Creator;
	}
	
	public BranchGroup GetSceneGraph()
	{
		return m_SceneGraph;
	}
	
	
	private BranchGroup m_SceneGraph;
	private ArgonJ3DDevice m_Creator;
}
