package testWeb.dao;
import java.util.List;

import java.sql.SQLException;


import testWeb.vo.*;

public interface RobotDAO {
	
	
	public List<RobotInfo> robotQuery() throws Exception;

    public boolean doCreate(RobotInfo robotinfo) throws Exception;
}
