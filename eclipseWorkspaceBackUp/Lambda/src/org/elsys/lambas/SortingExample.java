package org.elsys.lambas;

import java.util.Arrays;
import java.util.Comparator;

public class SortingExample {

	public SortingExample() {
	
	}

	public static void main(String[] args) {
		String[] words = new String[] {"1", "two", "three", "4", "five"};
		/*
		 * v java nqma tip function 
		 * suzdava se instanciq na anonimen klas(interface) i kompilatora namapva 
		 */
		//Sorting prior to Java 8
		Arrays.sort(words, new Comparator<String>() {
			
			@Override
			public int compare(String o1, String o2) {
				return o1.length() - o2.length();
			}
			
		});
		
		for (String string : words) {
			System.out.print(string + " ");
		}
		
		/*
		Arrays.sort(words,(String s1, String string2) -> {
			return s1.length() - s2.length();
		});
		*/
		
		Arrays.sort(words,(s1, s2) -> {
			return s1.length() - s2.length();
		});
		
		//new + easy
		Arrays.sort(words,(s1, s2) -> s1.length() - s2.length());
		Arrays.stream(words).forEach(word -> System.out.print(word + " "));
	}

}
