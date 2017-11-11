package objects;

import java.io.Serializable;

public class UpdateLevelRequest implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = -8051780252652573516L;
	private String username;
	private int level;

	public UpdateLevelRequest(String username, int level) {
		this.username = username;
		this.level = level;
	}
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
	public int getLevel() {
		return level;
	}
	public void setLevel(int level) {
		this.level = level;
	}
	
}
