/*
	HW: 
	1. Add Rectangle - done
	2. Add Line	- done
	3. Add Ellipse - done
	4. Add Polyline
	5. Add Polygone
*/

#include <iostream>
#include <list>
#include <cstring>
#include <sstream>
using namespace std;

class Point {
	int x_;
	int y_;
public:
	Point(int x=0, int y=0)
	: x_(x), y_(y)
	{}
	
	int get_x() const {
		return x_;
	}
	
	int get_y() const {
		return y_;
	}
};

class Styleable {
	string stroke_;
	string fill_;
	string style_;
public:
	Styleable()
	{}
	
	Styleable& set_stroke(string color) {
		stroke_=color;
		return *this;
	}
	
	Styleable& set_style(string style) {
		style_ = style;
		return *this;
	}
	
	string get_style() const {
		string result;
		if(!style_.empty()) {
			result = " style=\"" + style_ + "\" ";
			return result;
		}
		
		if(!stroke_.empty()) {
			result += " stroke=\"" + stroke_ + "\" ";
		}
		return result;
	}
	
};


class Shape: public Styleable {
public:
	virtual void draw() const = 0;
};


class Circle: public Shape {
	Point center_;
	int r_;
public:
	Circle(Point center, int r)
	: center_(center),
	  r_(r)
	{}
	
	void draw() const {
		cout << "<circle cx=\"" << center_.get_x() 
			 << "\" cy=\"" << center_.get_y()
			 << "\" r=\"" << r_
			 << "\" " << get_style()
			 << "/>" << endl;
	}
};

class Rectangle: public Shape {
	Point position_;
	int width_;
	int height_;
public:
	Rectangle(Point position, int width, int height)
	:	position_(position),
		width_(width),
		height_(height) 
	{}
	
	void draw() const {
		cout << "<rect x=\"" << position_.get_x()
			<< "\" y=\"" << position_.get_y() << "\" width=\"" 
			<< width_ << "\" height=\"" 
			<< height_ << "\" " << get_style() 
			<< "/>" << endl;
	}
};

class Line: public Shape {
	Point startcoord_;
	Point endcoord_;
public:
	Line(Point startcoord, Point endcoord)
	:	startcoord_(startcoord),
		endcoord_(endcoord)
	{}
	
	void draw() const {
		cout << "<line x1=\"" << startcoord_.get_x()
			<< "\" y1=\"" << startcoord_.get_y() << "\" x2=\"" 
			<< endcoord_.get_x() << "\" y2=\"" 
			<< endcoord_.get_y() << "\" " << get_style() 
			<< "/>" << endl;
	}
};

class Ellipse: public Shape {
	Point center_;
	Point r_;
public:
	Ellipse(Point center, Point r)
	:	center_(center),
		r_(r)
	{}
	
	void draw() const {
		cout << "<ellipse cx=\"" << center_.get_x() 
			 << "\" cy=\"" << center_.get_y()
			 << "\" rx=\"" << r_.get_x()
			 << "\" " << "ry=\"" << r_.get_y() <<
			 "\" " << get_style() << "/>" << endl;
	}
};

class Drawing {
	list<Shape*> shapes_;
public:
	void add(Shape* shape) {
		shapes_.push_back(shape);
	}

	void draw() const {
		cout << "<svg>" << endl;
		for(list<Shape*>::const_iterator it = shapes_.begin();
			it!=shapes_.end(); ++it) {
		
			(*it)->draw();	
		}
		cout << "</svg>" << endl;
	}
};


int main() {
	
	Drawing d;
	
	for(int i=0; i<50; ++i) {
		Circle* pc = new Circle(Point(i*10, i*10), i*5);
		ostringstream style;
		style << "stroke: red;"
			  << "stroke-width: " << 0.1*i << "; "
			  << "fill: rgb(" << i << "," << i << ", " << 3*i << ");"
			  << "fill-opacity: " << 0.1 + i*.005 << ";";
			  
		pc->set_style(style.str());
		d.add(pc);
	}
	
	
	d.draw();
	
	return 0;
}

