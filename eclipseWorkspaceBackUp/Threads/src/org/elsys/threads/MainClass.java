package org.elsys.threads;

import java.util.ArrayList;

public class MainClass {

	static Long counter = 0L;
	
	static Object lock = new Object();
	//lock.wait() goes to waiting state
	//lock.notify() awake lock(gets lock from wait end starts it)
	public static void main(String[] args) throws InterruptedException {
	
	}

	private static void secondExample() {
		ArrayList<Thread> threads = new ArrayList<>();
		for(int i = 0; i < 10; ++i) {
		//	threads.add(new Thread()//sth
		}
		
		for (Thread thread : threads) {
			thread.start();
		}
	}

	/**
	 * Extending java.lang.thread, implementing java.lang.runnable. Anonymous
	 * and named classes.
	 */
	private static void firstExample() {
		Thread thread = new ThreadImplementation(); // the thread has not
													// started yet
		thread.start();

		Thread runnable = new Thread(new Runnable() {

			@Override
			public void run() {
				while (true) {
					try {
						Thread.sleep(10);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					System.out.println("I am awake");
				}
			}
		});

		runnable.start();

		System.out.println("Exit from main");
	}

}
