package testWeb.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import testWeb.dao.*;
import testWeb.dao.impl.RobotDAOImpl;
import testWeb.dao.impl.UserDAOImpl;
import testWeb.vo.RobotInfo;

public class RobotQueryServlet extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse res) 
			throws IOException,ServletException{
	}
	public void doPost(HttpServletRequest req, HttpServletResponse res)
	        throws IOException,ServletException{
		RobotInfo robotinfo=new RobotInfo();
		robotinfo.setRobotID(req.getParameter("robotID"));
		robotinfo.setPath(req.getParameter("path"));
		robotinfo.setTime(req.getParameter("time"));
		RobotDAO dao=new RobotDAOImpl();
		int flag=0;
		try {
			dao.robotQuery();
		}catch(Exception e) {
			e.printStackTrace();
		}
		if(flag==1) {
			res.sendRedirect("./RobotInfo.jsp");
		}

		
	}
	

}
