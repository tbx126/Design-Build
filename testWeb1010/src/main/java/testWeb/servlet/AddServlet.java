package testWeb.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import testWeb.dao.UserDAO;
import testWeb.dao.impl.UserDAOImpl;
import testWeb.vo.UserInfo;

public class AddServlet extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse res) 
			throws IOException,ServletException{

	} 
	public void doPost(HttpServletRequest req, HttpServletResponse res)
	        throws IOException,ServletException{
		 PrintWriter out =res.getWriter();
		 UserInfo userinfo=new UserInfo();
		 userinfo.setUsername(req.getParameter("username"));
		 userinfo.setPassword(req.getParameter("password"));
		 UserDAO dao=new UserDAOImpl();
		 HttpSession session =req.getSession();
		 session.setAttribute("userinfo", userinfo);
		 boolean flag=false;
		 try {
			 
	
	            if(dao.addUser(userinfo)){
	               out.println("Successfully Register!");
	               out.println("Return to the login page in 3 seconds");
	             res.setHeader("Refresh","3;url=./login.jsp");
	          }
	            else{
	                out.println("The username is already exists!");
	               out.println("Return to the register page in 3 seconds");
	              res.setHeader("Refresh","3;url=./register.jsp");
	              
	           }
	        } catch (SQLException throwables) {
	            throwables.printStackTrace();
	        }finally {
	        	out.close();
	        }

		 
	}

	
}
