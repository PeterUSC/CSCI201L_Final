package networking;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Scanner;

import objects.CheckPlayerRequest;
import objects.CreatePlayerRequest;
import objects.GetLevelRequest;
import objects.UpdateLevelRequest;

public class Client{
	
	private ObjectInputStream ois;
	private ObjectOutputStream oos;
	private String hostname = "localhost";
	private int port = 5505;

	public Client() {
		try {
			 System.out.println("Trying to connet to: " + hostname + ":" + port);
			 Socket s = new Socket(hostname, port);
			 System.out.println("Connected to: " + hostname + ":" + port);
			 ois = new ObjectInputStream(s.getInputStream());
			 oos = new ObjectOutputStream(s.getOutputStream());
			 //call game function here
			 System.out.println("Run game here");
		 }catch(IOException ioe) {
			 System.out.println("ioe in ChatClient constructor: " + ioe.getMessage());
		 }
	}
	
	public Object readObject() throws ClassNotFoundException, IOException {
		return ois.readObject();
	}
	
	public void writeObject(Object obj) throws IOException {
		oos.writeObject(obj);
		oos.flush();
	}
	
	public static void main(String [] args) throws IOException, ClassNotFoundException {
		Client c = new Client();
		Scanner scanner = new Scanner(System.in);
		String input;
		String username;
		String password;
		String lvlString;
		int level;
		boolean end = false;
		while(end == false) {
			System.out.println("login, signup, getlevel, or updatelevel?");
			input = scanner.nextLine();
			
			if(input.equals("login")) {
				System.out.println("Username:");
				username = scanner.nextLine();
				System.out.println("Password");
				password = scanner.nextLine();
						
				CheckPlayerRequest cpr = new CheckPlayerRequest(username,password);
				c.writeObject(cpr);
				Object obj = c.readObject();
				if(obj instanceof Boolean) {
					boolean b = (boolean)obj;
					if(b == true) {
						System.out.println("Very well, you may now play the game");
					}else if(b == false) {
						System.out.println("You do not have an account yet.");
					}
				}
			}else if(input.equals("signup")) {
				System.out.println("Username:");
				username = scanner.nextLine();
				System.out.println("Password");
				password = scanner.nextLine();
				
				CreatePlayerRequest create = new CreatePlayerRequest(username, password, 0);
				c.writeObject(create);
				Object obj = c.readObject();
				if(obj instanceof Boolean) {
					boolean b = (boolean)obj;
					if(b == true) {
						System.out.println("Very well, you may now play the game");
					}else if(b == false) {
						System.out.println("Failed to create an account.");
					}
				}
			}else if(input.equals("getlevel")) {
				System.out.println("Username:");
				username = scanner.nextLine();
				
				GetLevelRequest glr = new GetLevelRequest(username);
				c.writeObject(glr);
				Object obj = c.readObject();
				if(obj instanceof Integer) {
					int out = (int) obj;
					System.out.println("Got level: " + out);
				}
			}else if(input.equals("updatelevel")) {
				System.out.println("Username:");
				username = scanner.nextLine();
				System.out.println("level:");
				lvlString = scanner.nextLine();
				level = Integer.parseInt(lvlString);
				
				UpdateLevelRequest ulr = new UpdateLevelRequest(username, level);
				c.writeObject(ulr);
				Object obj = c.readObject();
				if(obj instanceof Boolean) {
					boolean b = (boolean)obj;
					if(b == true) {
						System.out.println("Update Successful");
					}else if(b == false) {
						System.out.println("Update Failed");
					}
				}
			}
		}
		
		scanner.close();
	}
}
