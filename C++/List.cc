#include <iostream>

using namespace std; 

class ListError {
	int status_;
public:
	ListError(int status) {
		status_ = status;
	}
	
	int get_status() {
		return status_;
	}
};

class List {
	struct Node {
		int data_;
		Node* prev_;
		Node* next_;
		
		Node(int val = 0) 
		: data_(val), prev_(0), next_(0)
		{}
	};

	Node* head_;
public:
	List()
	:	head_(new Node())
	{
		head_->prev_ = head_;
		head_->next_ = head_;
	}
	
	~List() {
		while(!is_empty()) {
			pop_back();
		}
		delete head_;
	}
	
	bool is_empty() const {
		return head_->prev_ == head_;
	}
	
	void push_front(int val) {
		Node* new_node = new Node(val);
		Node* front_node = head_->next_;
		
		head_->next_ = new_node;
		new_node->prev_ = head_;
		
		new_node->next_ = front_node;
		front_node->prev_ = new_node;
	}
	
	void push_back(int val) {
		Node* new_node = new Node(val);
		Node* back_node = head_->prev_;
		
		head_->prev_ = new_node;
		new_node->next_ = back_node;
		
		new_node->prev_ = head_;
		back_node->next_ = new_node;
	}
	
	void pop_front() {
		if(is_empty()) {
			throw ListError(1);
		}
		Node* front_node = head_->next_;
		head_->next_ = front_node->next_;
		front_node->next_->prev_ = head_;
		delete front_node;
	}
	
	void pop_back() {
		if(is_empty()) {
			throw ListError(1);
		}
		Node* back_node = head_->prev_;
		head_->prev_ = back_node->prev_;
		back_node->next_ = head_;
		delete back_node;
	}
	
	int front() const {
		if(is_empty()) {
			throw ListError(1);
		}
		return head_->next_->data_;
	}
	
	int back() const {
		if(is_empty()) {
			throw ListError(1);
		}
		return head_->prev_->data_;
	}
};

int main() {
	List l;
	try{
		cout << "is_empty =  " << l.is_empty() << endl << endl;
		for(int i = 0; i < 5; ++i) l.push_front(i);
		cout << "is_empty =  " << l.is_empty() << endl << endl;
		cout << l.front() << ", " << l.back() << endl;
		cout << "is_empty =  " << l.is_empty() << endl << endl;
	}catch(ListError lerr) {
		cout << "Exeption Catched:" << endl;
		cout << "\t@status = " << lerr.get_status() << ":  can't pop() on empty list" << endl;
	}
	return 0;
}












