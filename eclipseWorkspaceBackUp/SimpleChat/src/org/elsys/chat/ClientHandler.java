package org.elsys.chat;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class ClientHandler implements Runnable {
	
	private ChatServer server;
	private Socket client;
	private String username;
	
	public ClientHandler(String username, Socket socket, ChatServer server) {
		this.username = username;
		this.client = socket;
		this.server = server;
	}

	private boolean isLogin(Scanner input) {
		String firstStr = input.next();
		firstStr.toLowerCase();
		return "login".equals(firstStr);
	}
	
	@Override
	public void run() {
		try(
			Scanner inScanner = new Scanner(client.getInputStream());
			if(isLogin(inScanner)) {
				
			}
			PrintWriter outWriter = new PrintWriter(client.getOutputStream(), true);
		){
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		

	}

}
