package org.elsys.threads101;

import java.util.Arrays;
import java.util.List;

public class MainClass {
	
	public static void main(String[] args) {
		List<String>names=Arrays.asList("Aristotel", "Plato", "Thales", "Pythagor", "Heraclis");
		Table table = new Table(5);
		for(int i = 0; i < 5; i++) {
			Philosopher p = new Philosopher(i, table, names.get(i));
			new Thread(p).start();
		}
	}

}
