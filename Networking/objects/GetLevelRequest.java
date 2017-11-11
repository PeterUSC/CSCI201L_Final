package objects;

import java.io.Serializable;

public class GetLevelRequest implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = -5568806040789650282L;
	String username;

	public GetLevelRequest(String username) {
		this.username = username;
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}
	
}
