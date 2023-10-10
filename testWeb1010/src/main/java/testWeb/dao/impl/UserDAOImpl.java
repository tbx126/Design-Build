package testWeb.dao.impl;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.http.HttpServletResponse;

import testWeb.dao.UserDAO;
import testWeb.db.DBConnect;
import testWeb.vo.UserInfo;

public class UserDAOImpl implements UserDAO {

	public int queryByUserInfo(UserInfo userinfo) throws Exception {
		int flag=0;
		String sql="select * from userinfo where username=?";
		PreparedStatement pstmt=null;
		DBConnect dbc=null;
		
		try {
			//连接数据库
			dbc=new DBConnect();
			pstmt=dbc.getConnection().prepareStatement(sql);
			pstmt.setString(1, userinfo.getUsername());
			//数据库查询
			ResultSet rs=pstmt.executeQuery();
			while(rs.next()) {
				//查询后对比
				if(rs.getString("password").equals(userinfo.getPassword())) {
					flag=1;
				}
			}
			rs.close();
			pstmt.close();
		}catch(SQLException e) {
			System.out.println(e.getMessage());
		}finally {
			dbc.close();
		}
		
		return flag;
	}

	public boolean addUser(UserInfo userinfo) throws SQLException{
		boolean flag=true;

		PreparedStatement pstmt1=null;
		PreparedStatement pstmt2=null;
		DBConnect dbc=null;

		try {
			dbc=new DBConnect();
			String sql2="select * from userinfo where username=?";
			pstmt2=dbc.getConnection().prepareStatement(sql2);
			pstmt2.setString(1, userinfo.getUsername());
			ResultSet rs=pstmt2.executeQuery();
			
			while(rs.next()) {
				//查询后对比
				if(rs.getString("username").equals(userinfo.getUsername())) {
					flag=false;
			
				}}
			
				if(flag) {
					String sql1="insert into userinfo(username,password) values(?,?)";
					pstmt1=dbc.getConnection().prepareStatement(sql1);
					pstmt1.setString(1, userinfo.getUsername());
					pstmt1.setString(2, userinfo.getPassword());
					int res=pstmt1.executeUpdate();
					if(res>0) {
						flag=true;
					}}
				
			rs.close();
			if(pstmt1!=null) {
				pstmt1.close();
			}
			if(pstmt2!=null) {
				pstmt2.close();
			}
			
		}catch(SQLException e) {
			System.out.println(e.getMessage());
		}finally {
			dbc.close();
		}
		return flag;
	}
}
