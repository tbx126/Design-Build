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

<h2>Robotinfo Manage System</h2>
<a href="http://192.168.8.1/video.html">View car real-time dynamics</a> 

&nbsp;&nbsp;&nbsp;

</form>
<table border="1" style="width: 100%;" cellspacing="0">
    <tr style="text-align: center; background-color:#ffaa00;">
        <th>ID</th>
        <th>runtime</th>
        <th>path</th>
        <th>detection result</th>
    
    </tr>
    <c:forEach items="${list}" var="robotinfo">
    
   
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
String sql = "SELECT * FROM robotinfo;"; //查询语句
stmt = conn.createStatement();
rs = stmt.executeQuery(sql);

out.print("<br/>");
while (rs.next()) {
%>
<tr>
<td><%=rs.getString("robotID")%></td>
<td><%=rs.getString("time")%></td>
<td><%=rs.getString("path")%></td>
<td><%=rs.getString("result")%></td>

</tr>

<%
}%>

</tr>
      
    </c:forEach>
</table>
<div style="float: right;">
 

</div>
</body>
</html>


