package testWeb.dao.impl;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import testWeb.dao.RobotDAO;
import testWeb.db.DBConnect;
import testWeb.vo.RobotInfo;

public class RobotDAOImpl implements RobotDAO {

	@Override
	public List<RobotInfo> robotQuery() throws Exception {
		
		String sql="select * from robotinfo";
		PreparedStatement pstmt=null;
		DBConnect dbc=null;
		ResultSet rs=null;
		List<RobotInfo> all=new ArrayList<RobotInfo>();
	
		try {
			dbc=new DBConnect();
			pstmt=dbc.getConnection().prepareStatement(sql);
			rs =pstmt.executeQuery();
			while(rs.next()) {
				RobotInfo robotinfo=new RobotInfo();
				robotinfo.setRobotID(rs.getString(1));
				robotinfo.setPath(rs.getString(2));
				robotinfo.setTime(rs.getString(3));

			  all.add(robotinfo);
			  int flag=1;
			}
			rs.close();
			pstmt.close();		    
		}catch(SQLException e) {
			System.out.println(e.getMessage());
		}finally {
			dbc.close();
		}
		return all;
	}

	@Override
	public boolean doCreate(RobotInfo robotinfo) throws Exception {
		// TODO Auto-generated method stub
		return false;
	}

}

