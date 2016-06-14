package org.elsys.threads;

public class SynchronizedLong {
	
	private Long value;
	
	public SynchronizedLong(Long value) {
		this.value = value;
	}
	
	public Long getValue() {
		return value;
	}
	
	//synchronizes on this
	public synchronized void increment() {
		value++;
	}
}
