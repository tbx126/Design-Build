package testWeb.db;

import java.sql.Connection;
import java.sql.DriverManager;

public class DBConnect {
	private final String DBDRIVER ="com.mysql.cj.jdbc.Driver";
	private final String DBURL="jdbc:mysql://127.0.0.1:3306/javawebdb?useSSL=false&serverTimezone=UTC";
	private final String DBUSER="root";
	private final String DBPASSWORD="ckn12345";
	private Connection conn=null;
	
	public DBConnect() {
		try {
			Class.forName(DBDRIVER);
			this.conn=DriverManager.getConnection(DBURL,DBUSER,DBPASSWORD);
		}catch(Exception e) {
			System.out.println(e.getMessage());
		}
	}
	//取得数据库连接
	public Connection getConnection() {
		return this.conn;
	}
	public void close() {
		try {
			this.conn.close();
		}catch(Exception e) {}
	}

}





