package org.elsys.chat;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import org.elsys.sockets.ClientHandler;

public class ChatServer extends Thread{

	private ServerSocket socket;
	private ExecutorService threadPool;
	private boolean running = true;
	private Map<String, Socket> clients = new HashMap<>();
	
	public ChatServer(int port) {
		try {
			socket = new ServerSocket(port);
		} catch (IOException e) {
			System.err.println("Port already in use");
			System.exit(-1);
		}
		
		System.out.println("Chat server started on " + port);
		threadPool = Executors.newFixedThreadPool(29);
	}
	
	@Override
	public void run() {
		while(running) {
			try {
				ClientHandler clientHandler = new ClientHandler();
				threadPool.submit(clientHandler);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	private void shutDown() {
		System.out.println("Server shutting down ...");
		running = false;
		try{
			socket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		new ChatServer(4444).start();;
	}

}
