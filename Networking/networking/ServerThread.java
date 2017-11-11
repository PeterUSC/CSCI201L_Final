package networking;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import objects.CheckPlayerRequest;
import objects.CreatePlayerRequest;
import objects.GetLevelRequest;
import objects.UpdateLevelRequest;

public class ServerThread extends Thread {
	private Server server;
	private ObjectOutputStream oos;
	private ObjectInputStream ois;
	
	public ServerThread(Socket s, Server server) {
		try {
			this.server = server;
			oos = new ObjectOutputStream(s.getOutputStream());
			ois = new ObjectInputStream(s.getInputStream());
			this.start();
			
		} catch(IOException ioe) {
			System.out.println("ioe in ServerThread constructor: " + ioe.getMessage());
		}
	}
	
	public int checkInputs(String username, String password, int level, int operation) {
		if(username == null) {
			return 1; //no username
		}
		if(password == null) {
			return 2; //no password
		}
		
		if(operation == 0) {
			//call createPlayer
			createPlayer(username, password, level);
			return 0;
		}else if(operation == 1){
			//call check player
			checkPlayer(username, password);
			return 0;
		}else if(operation == 2) {
			//call getLevel
			getLevel(username);
			return 0;
		}else if(operation == 3) {
			//call updateLevel
			updateLevel(username, level);
			return 0;
		}
		
		return 3;
	}	
		
	public boolean createPlayer(String username, String password, int level) {
		Connection conn = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		
		try {
			Class.forName("com.mysql.jdbc.Driver");
			conn = DriverManager.getConnection("jdbc:mysql://localhost/PlayerBase?user=root&password=root");
			ps = conn.prepareStatement("SELECT * FROM player WHERE username=?");
			ps.setString(1, username);
			rs = ps.executeQuery();
		
			while(rs.next()) {
				if (rs != null) {
					rs.close();
				}
				if(ps != null) {
					ps.close();
				}
				if(conn != null) {
					conn.close();
				}
				
				return false;
			}
			
			//if here, then username does not exist use SQL code to create player
			ps = conn.prepareStatement("INSERT INTO player(username, password, levelcompleted) VALUES(?,?,?)");
			ps.setString(1, username);
			ps.setString(2, password);
			ps.setInt(3, level);
			int result = ps.executeUpdate();
			if(result == 0) {
				return false;
			}
			
		}catch(SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		}catch(ClassNotFoundException cnfe) {
			System.out.println("cnfe: " + cnfe.getMessage());
		} finally {
			try {
				if (rs != null) {
					rs.close();
				}
				if(ps != null) {
					ps.close();
				}
				if(conn != null) {
					conn.close();
				}
			}catch(SQLException sqle) {
				System.out.println("sqle closing stuff: " + sqle.getMessage());
			}
		}
		
		return true;
		
	}
	
	public boolean checkPlayer(String username, String password) {
		Connection conn = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		String u = "";
		String p = "";
		try {
			Class.forName("com.mysql.jdbc.Driver");
			conn = DriverManager.getConnection("jdbc:mysql://localhost/PlayerBase?user=root&password=root");
			ps = conn.prepareStatement("SELECT * FROM player WHERE username=? AND password=?");
			ps.setString(1, username);
			ps.setString(2, password);
			rs = ps.executeQuery();
			
			while(rs.next()) {
				u = rs.getString("username");
				p = rs.getString("password");
			}
			
			if(u.equals(username) && p.equals(password)) {
				return true;
			}
		
		
		}catch(SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		}catch(ClassNotFoundException cnfe) {
			System.out.println("cnfe: " + cnfe.getMessage());
		} finally {
			try {
				if (rs != null) {
					rs.close();
				}
				if(ps != null) {
					ps.close();
				}
				if(conn != null) {
					conn.close();
				}
			}catch(SQLException sqle) {
				System.out.println("sqle closing stuff: " + sqle.getMessage());
			}
		}
		
		return false;
	}
	
	public int getLevel(String username) {
		Connection conn = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		int level = 0;
		try {
			Class.forName("com.mysql.jdbc.Driver");
			conn = DriverManager.getConnection("jdbc:mysql://localhost/PlayerBase?user=root&password=root");
			ps = conn.prepareStatement("SELECT levelcompleted FROM player WHERE username=?");
			ps.setString(1, username);
			rs = ps.executeQuery();
			
			while(rs.next()) {
				level = rs.getInt("levelcompleted");
			}
		}catch(SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		}catch(ClassNotFoundException cnfe) {
			System.out.println("cnfe: " + cnfe.getMessage());
		} finally {
			try {
				if (rs != null) {
					rs.close();
				}
				if(ps != null) {
					ps.close();
				}
				if(conn != null) {
					conn.close();
				}
			}catch(SQLException sqle) {
				System.out.println("sqle closing stuff: " + sqle.getMessage());
			}
		}
		
		return level;
	}
	
	private boolean updateLevel(String username, int level) {
		Connection conn = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			Class.forName("com.mysql.jdbc.Driver");
			conn = DriverManager.getConnection("jdbc:mysql://localhost/PlayerBase?user=root&password=root");
			ps = conn.prepareStatement("UPDATE player SET levelcompleted=? WHERE username=?");
			ps.setInt(1,level);
			ps.setString(2, username);
			int result = ps.executeUpdate();
			
			if(result == 0) {
				return false;
			}
			
		}catch(SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		}catch(ClassNotFoundException cnfe) {
			System.out.println("cnfe: " + cnfe.getMessage());
		} finally {
			try {
				if (rs != null) {
					rs.close();
				}
				if(ps != null) {
					ps.close();
				}
				if(conn != null) {
					conn.close();
				}
			}catch(SQLException sqle) {
				System.out.println("sqle closing stuff: " + sqle.getMessage());
			}
		}
		
		return true;
	}
	
	public void run() {
		boolean finish = false;
		try {
			while(finish == false) {
				Object obj = ois.readObject();
				if(obj instanceof CreatePlayerRequest) {
					CreatePlayerRequest create = (CreatePlayerRequest)obj;
					boolean output = createPlayer(create.getUsername(),create.getPassword(),0);
					oos.writeObject(output);
					oos.flush();
				}else if(obj instanceof CheckPlayerRequest) {
					CheckPlayerRequest check = (CheckPlayerRequest) obj;
					boolean output = checkPlayer(check.getUsername(), check.getPassword());
					oos.writeObject(output);
					oos.flush();
				}else if(obj instanceof GetLevelRequest) {
					GetLevelRequest get = (GetLevelRequest) obj;
					int output = getLevel(get.getUsername());
					oos.writeObject(output);
					oos.flush();
				}else if(obj instanceof UpdateLevelRequest) {
					UpdateLevelRequest update = (UpdateLevelRequest) obj;
					boolean output = updateLevel(update.getUsername(),update.getLevel());
					oos.writeObject(output);
					oos.flush();
				}else if(obj instanceof String) {
					String input = (String)obj;
					if(input.equals("exit")){
						finish = true;
					}
				}
			}
		} catch (ClassNotFoundException cnfe) {
			System.out.println(cnfe.getMessage());
			cnfe.printStackTrace();
		} catch (IOException ioe) {
			System.out.println(ioe.getMessage());
			ioe.printStackTrace();
		}
	}
	
}
