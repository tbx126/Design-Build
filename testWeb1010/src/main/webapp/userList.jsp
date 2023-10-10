<%@ page language="java" contentType="text/html; charset=UTF-8"
         pageEncoding="UTF-8" %>
<%@page import="java.sql.*"%>
<%--导入java.sql包--%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Robotinfo Manage System</title>
</head>
<body>


&nbsp;&nbsp;&nbsp;

<a href="mainPage.jsp">back</a>
<form style="padding-bottom: 10px;">
    <fieldset>
        <legend>Search</legend>
        name:<input type="text" name="username" id="">
        <input hidden type="text" name="action" value="selectUser">
        <input type="submit" value="Search">
    </fieldset>
</form>
<table border="1" style="width: 100%;">
    <tr style="text-align: center; background-color:#ffaa00;">
        <th>ID</th>
        <th>name</th>
        <th>password</th>
      
      
     
       
    </tr>
    <c:forEach items="${userInfos}" var="userInfo">
       
 <%

Class.forName("com.mysql.cj.jdbc.Driver"); //驱动程序名
String url = "jdbc:mysql://127.0.0.1:3306/javawebdb?useSSL=false&serverTimezone=UTC"; //数据库名
String username = "root"; //数据库用户名
String password = "ckn12345"; //数据库用户密码
Connection conn = DriverManager.getConnection(url, username, password); //连接状态

%>
   

  <%
Statement stmt = null;
ResultSet rs = null;
String sql = "SELECT * FROM userinfo;"; //查询语句
stmt = conn.createStatement();
rs = stmt.executeQuery(sql);

out.print("<br/>");
while (rs.next()) {
%>
<tr>
<td><%=rs.getString("userinfoid")%></td>
<td><%=rs.getString("username")%></td>
<td><%=rs.getString("password")%></td>


</tr>

<%
}%>

</tr>      

    </c:forEach>
</table>
<div style="float: right;">
    <a href="register.jsp">Add</a>
   
</div>
</body>
</html>