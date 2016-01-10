#include <iostream>

#define STACK_SIZE 10

using namespace std;

class StackError {
	int status_;
public:
	StackError(int status) {
		status_ = status;
	}
	
	int get_status() {
		return status_;
	}
};

class Stack {
	int capacity_;
	int top_;
	int *data_;
	
	void stack_resize() {
		cout << "stack_resize() called ..." << endl;
		int *temp;
		temp = new int[capacity_];
		for(int i = 0; i < capacity_; ++i) {
			temp[i] = data_[i];
		}
		capacity_ *= 2;
		data_ = new int[capacity_];
		for(int i = 0; i < top_; ++i) {
			data_[i] = temp[i];
		}
		delete [] temp;
	}
	
public:
	Stack(int capacity = STACK_SIZE) 
	: capacity_(capacity), top_(0), data_(new int[capacity_])
	{}
	
	~Stack() {
		delete [] data_;
	}
	
	bool is_empty() {
		return top_ == 0;
	}
	
	bool is_full() {
		return top_ == capacity_;
	}
	
	void push(int val) {
		if(is_full()) {
			stack_resize();
		}
		data_[top_++] = val;
	}
	
	int pop() {
		if(is_empty()) {
			throw StackError(2);
		}
		return data_[--top_];
	}
};

int main() {
	Stack st;
	for(int i = 0; i < 1000; ++i) st.push(i);
	try{
		for(int i = 0; i < 1001; ++i) cout << st.pop() << endl;
	}catch(StackError sterr) {
		cout << "exeption catched" << endl;
		cout << "status = " << sterr.get_status() << ": can't pop() on empty stack" << endl;
	}
	return 0;
}



