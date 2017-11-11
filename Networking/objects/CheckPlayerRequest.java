package objects;

import java.io.Serializable;

public class CheckPlayerRequest implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 4833789669097327720L;
	String username;
	String password;
	public CheckPlayerRequest(String username, String password) {
		super();
		this.username = username;
		this.password = password;
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
	
}
