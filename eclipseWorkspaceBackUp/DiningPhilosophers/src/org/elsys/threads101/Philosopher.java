package org.elsys.threads101;

import java.util.Random;
import java.util.concurrent.locks.ReentrantLock;

public class Philosopher implements Runnable {
	private  int position;
	private Table table;
	private Random random;
	String name;
	
	public Philosopher(int position, Table table, String name) {
		this.position = position;
		this.table = table;
		this.random = new Random();
		this.name = name;
	}

	@Override
	public void run() {
		while(true) {
			think();
			System.out.println(name + " is hungry!");
			getForks();
			eat();
			putForks();
		}
	}
	
	private void putForks() {
		table.left(position).unlock();
		table.right(position).unlock();
	}
	
	private void getForks() {
		if(position % 5 == 0) {
			table.left(position).lock();
			table.right(position).lock();
		}else{
			table.right(position).lock();
			table.left(position).lock();
		}
	}
	
	private void eat() {
		try {
			Thread.sleep(random.nextInt(1000));
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private void think() {
		try {
			Thread.sleep(random.nextInt(1000));
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
