package networking;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Vector;

public class Server{
	
	private Vector<ServerThread> serverThreads;
	private int port = 5505;
	
	public Server(){
		try {
			System.out.println("Binding to port " + port);
			ServerSocket ss = new ServerSocket(port);
			System.out.println("Bound to port " + port);
			serverThreads = new Vector<ServerThread>();
			while(true) {
				Socket s = ss.accept(); //blocking line, waits for a connection
				System.out.println("Connection from: " + s.getInetAddress());
				ServerThread st = new ServerThread(s, this);
				serverThreads.add(st);
			}
		} catch(IOException ioe) {
			System.out.println("ioe in ChatRoom Constructor" + ioe.getMessage());
		}
	}
	
	public static void main(String [] args) {
		Server s = new Server();
	}
	
}

