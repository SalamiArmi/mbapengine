import java.applet.Applet;
import java.awt.BorderLayout;
import java.awt.Frame;
import java.awt.event.*;
import com.sun.j3d.utils.applet.MainFrame;
import com.sun.j3d.utils.timer.J3DTimer;
import com.sun.j3d.utils.universe.*;
import com.sun.j3d.utils.geometry.ColorCube;
import javax.media.j3d.*;
import javax.vecmath.*;

public class Main 
{
	public static void main(String[] args)
	{
		ArgonJ3DDevice Device = new ArgonJ3DDevice();
		MainFrame Frame = new MainFrame(Device, 256, 256);
		
		while(true)
		{
			Device.Update(java.lang.System.nanoTime());
			Device.Render();
		}
	}

}
