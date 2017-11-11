package objects;

import java.io.Serializable;

public class CreatePlayerRequest implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 7329298293487487157L;
	String username;
	String password;
	int level;
	
	public CreatePlayerRequest(String username, String password, int level) {
		this.username = username;
		this.password = password;
		this.level = level;
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public int getLevel() {
		return level;
	}

	public void setLevel(int level) {
		this.level = level;
	}
	
	
	
}
