package org.elsys.threads101;

import java.util.List;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Table {
	private List<ReentrantLock> forks;
	public Table(int size) {
		forks = IntStream.range(0, size)
				.mapToObj(x -> new ReentrantLock()).collect(Collectors.toList());
	}
	
	public void seat() {
		synchronized (counter) {
			while(counter.equals(4)) {
				counter.wait();
			}
		}
	}
	
	public void unseat() {
		synchronized (counter) {
				counter.addAndGet(-1);
				counter.notifyAll();
		}
	}
	
	public ReentrantLock left(int position) {
		return forks.get((position + 1) % forks.size());
	}
	
	public ReentrantLock right(int position) {
		return forks.get(position);
	}

}
