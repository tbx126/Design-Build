<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<<!DOCTYPE html>
<html>
	<head>
		<meta charset="ISO-8859-1">
		<title>div+css</title>
<style>
	#content{
		width: 1400px;
	}
	#top{
		width: 100%;
		height: 100px;
		border: 1px solid red;
	}
	#center{ 
		width: 100%;
		height: 450px;
		/*border: 1px solid black;*/
		margin-top: 12px;
		/*上外边距 */
	}
	#left{ 
		width: 550px;
		height: 450px; 
		border: 4px solid blue;
		float: left; 
		
		/*浮动   left 左浮动  right 右浮动*/
	}
	#right{
		width: 800px;
		height: 450px;
		border: 4px solid green;
		float: right;
	}
	#footer{
		width: 100%;
		height: 100px;
		border: 2px solid darkmagenta;
		margin-top: 12px;
	}
</style>		
	</head>
	<body>
		<div id="content">
			<div  id="top">
			
			
			<h1 align="center">The robot manage system</h1>
			<%String username = (String)session.getAttribute("username"); %>
		<marquee>
			WELCOM! Administrator <%= username %>, LOGIN SUCCESSFULLY!!
		</marquee>
			
			
			<div id="center">
				
				<div id="left">
				
				<h2> Direction </h2>
	
	
		<a href="userList.jsp">Manage User information</a>
		  
		 <br /><br />  
		 
		<a href="RobotInfo.jsp">View Robot information</a>
		
		<br /><br /> 
		</div>
		
				
				<div  id="right"><h1 align="center">Page Details</h1>
		<hr color="red" />
		<font align="center" color="cadetblue" size="1" >
		<a href="login.jsp">Log out</a>
		</div>
			</div>
			<div id="footer"><p align="center"> 
			
			copyright &copy; || contain us||2023.6.27 <br />
			Addr: 123.2023
			</div>
		</div>
	</body>
</html>