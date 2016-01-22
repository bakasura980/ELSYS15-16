#include <iostream>

using namespace std;

class RationalError {
	int status_;
public:
	RationalError(int status) {
		status_ = status;
	}
	
	int get_status() {
		return status_;
	}
};

class Rational {
	long num_;
	long den_;
	
	long gcd(long a, long b) {
		long r = a % b;
		while(r != 0) {
			a = b;
			b = r;
			r = a % b;
		}
		return b;
	}
	
	void normalize() {
		if(num_ == 0) {
			den_ = 1;
			return;
		}
		long d = gcd(num_, den_);
		num_ /= d;
		den_ /= d;
		if(den_ < 0) {
			num_ = -num_;
			den_ = -den_;
		}
	}
public:
	Rational(long num, long den) {
		if(den == 0) {
			throw RationalError(1);
		}
		num_ = num;
		den_ = den;
		normalize();
	}
	
	void add(Rational other) {
		num_ = num_*other.den_ + den_*other.num_;
		den_ *= other.den_;
		normalize();
	}
	
	void sub(Rational other) {
		num_ = num_*other.den_ - den_*other.num_;
		den_ *= other.den_;
		normalize();
	}
	
	void mul(Rational other) {
		num_ *= other.num_;
		den_ *= other.den_;
		normalize();
	}
	
	void div(Rational other) {
		if(other.den_ == 0) {
			throw RationalError(1);
		}
		num_ /= other.num_;
		den_ /= other.den_;
		normalize();
	}
	
	bool equal(Rational other) {
		return num_ == other.num_ && den_ == other.den_;
	}
	
	bool greater(Rational other) {
		return num_ * other.den_ > den_ * other.num_;
	}
	
	void print() {
		cout << '(' << num_ << '/' << den_ << ')' << endl;
	}
};

int main() {
	Rational r(3, 6);
	Rational r1(1, 2);
	try{
		r.add(r1);r.print();
		r.sub(r1);r.print();
		r.mul(r1);r.print();
		r.div(r1);r.print();
		cout << r.equal(r1) << endl;
		cout << r.greater(r1) << endl;
	}catch(RationalError rerr) {
		cout << "Exeption Catched\n";
		if(rerr.get_status() == 1) {
			cout << "\t@status = " << 1 << ": cannot zero division\n" << endl;
		}
	}
	return 0;
}



