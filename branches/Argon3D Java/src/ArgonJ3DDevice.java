import java.applet.Applet;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Frame;
import java.awt.GraphicsConfiguration;
import java.awt.event.*;
import java.util.Random;
import com.sun.j3d.utils.applet.MainFrame;
import com.sun.j3d.utils.universe.*;
import com.sun.j3d.utils.geometry.ColorCube;
import javax.media.j3d.*;
import javax.vecmath.*;

public class ArgonJ3DDevice extends Applet
{
	public ArgonJ3DDevice()
	{
		setLayout(new BorderLayout());
		GraphicsConfiguration Config = SimpleUniverse.getPreferredConfiguration();
		m_Canvas = new Canvas3D(Config);
		add("Center", m_Canvas);
				
		m_Universe = new SimpleUniverse(m_Canvas);
		m_Universe.getViewingPlatform().setNominalViewingTransform();
	}
	
	public void Update(float DeltaT)
	{
		
	}
	
	public boolean Render()
	{
		return false;
	}
	
	public ArgonJ3DSceneManager CreateSceneManager(String Name)
	{
		ArgonJ3DSceneManager Scene = new ArgonJ3DSceneManager(Name, this);
		m_Universe.addBranchGraph(Scene.GetSceneGraph());
		
		return Scene;
	}
	
	public void SetSceneManager(ArgonJ3DSceneManager Scene)
	{
		m_Scene = Scene;
	}
	
	////////////////////////////////////////////////
	// Java3D
	private Canvas3D m_Canvas;	
	private SimpleUniverse m_Universe;

	///////////////////////////////////////////////
	// Argon
	private ArgonJ3DSceneManager m_Scene;
}
