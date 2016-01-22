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
	
	class iterator {
		Node* node_;
		
		iterator(Node* node)
		: node_(node)
		{}
		
		friend class List;
	public:
		int& operator*() {
			return node_->data_;
		}
		
		iterator& operator++() {
			node_ = node_->next_;
			return *this;
		}
		
		iterator operator++(int) {
			iterator res(*this);
			node_ = node_->next_;
			return res;
		}
		
		bool operator==(const iterator& other) const {
			return node_==other.node_;
		}
		
		bool operator!=(const iterator& other) const {
			return !(operator==(other));
		}
	};
	
	iterator begin() {
		return iterator(head_->next_);
	}
	
	iterator end() {
		return iterator(head_->prev_);
	}
	
	List(const List& other)
	:
	{
		~List();
		List l = new List(other);
		iterator it = other.begin();
		for(it; it != other.end(); ++it) {
			l[it] = other[it];
		}
	}
	
	List& operator=(const List& other) {
		if(this != other) {
			List(other);
		}
		return *this;
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
	
	List::iterator it = l.begin();
	cout << "l.begin() = " << *it << endl;
	for(it; it != l.end(); ++it) cout << *it << ' ';
	cout << endl;
	return 0;
}












