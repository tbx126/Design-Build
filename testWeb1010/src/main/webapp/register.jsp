<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>

<!DOCTYPE html>
<html>
	<head>
		<meta charset="ISO-8859-1">
		<title>Register</title>
	</head>
	<body bgcolor="cornflowerblue">
		<!--form 表单-->
		<h2>REGISTER</h2>
		<form method="post" action="./register">
			
			
			Username: <input type="text" name="username"/>  <br /><br /> 
			
			
		
			Passward:
			<input type="text" name="password"/>				  <br /><br />
	
		
			
			
			<br /><br />
			
			
			<tr>
			<td><input type="Submit" name="submit" value="Submit"/>
			<!--提交按钮的作用: 把form表单中的元素值  提交给  action 
				传值通过  name 属性  来 传
			--></td>
			</tr>
			
			<tr>
			
			<td>
			<input type="Reset" value="reset" />
			<a href="login.jsp">Back to login</a>
						<!--超链接 标签    a   href: 链接的地址-->
						</td>
						</tr>
						
		</form>
	</body>
</html>
