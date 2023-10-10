package testWeb.dao;

import java.sql.SQLException;

import testWeb.vo.UserInfo;

public interface UserDAO {
	public int queryByUserInfo(UserInfo userinfo) throws Exception;
	public boolean addUser(UserInfo userinfo) throws SQLException;
	
}
