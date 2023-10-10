package testWeb.vo;

import java.sql.Time;
import java.time.format.DateTimeFormatter;

public class RobotInfo {
	private String robotID;
	private String path;
	private String time ;
	private String result;
	
	public String getRobotID() {
		return robotID;
	}
	public void setRobotID(String robotID) {
		this.robotID = robotID;
	}
	
	public String getPath() {
		return path;
	}
	public void setPath(String path) {
		this.path = path;
	}
	
	public String getTime() {
		return time;
	}
	public void setTime(String time) {
		this.time = time;
	}
	
	public String getResult() {
		return result;
	}
	public void setResult(String result) {
		this.result = result;
	}

	
	

}
