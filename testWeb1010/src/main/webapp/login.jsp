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
			
			
			<h1 align="center">LOGIN the robot manage system</h1> </div>
			
			
			<div id="center">
				
				<div id="left">
				
				<img src="../G:/2023.7XXQ/robotShow.jpg" alt="ROBOT"  width="4096Xpx" height="1549px" > 
				
				</div>
				
				<div  id="right"><h2 align="center">Welcom to use Robot Manage System</h2>
		
		<br /><br /><br /><br /><br /><br />
		<form method="post" action="./login">
			<table border="0" align="center" cellspacing="0">
				<tr> 
					<td>username</td>
					<td><input type="text" name="username" /> </td> 
				</tr> 
				<tr>  
					<td>password</td>
					<td><input type="text" name="password"/> </td>
				</tr>
				<tr align="center">
					<td colspan="2">
						<input type="SUBMIT" name="submit" value="Submit"> 
						<a href="register.jsp">register</a>
						<!--超链接 标签    a   href: 链接的地址-->
				<br /><br />
		
			    <br /><br />  
						
			
						
					</td>
				</tr>
			</table>
		</form> 
		</div>
			</div>
			<div id="footer"><p align="center"> 
			
			copyright &copy; || contain us||2023.6.27 <br />
			Addr: 123.2023
			</div>
		</div>
	</body>
</html>