#include <iostream>
#include <cmath>
using namespace std;
const double EPS = 0.0000001;
const double TAU = 6.28318530717958647692528;
const double PI = TAU/2.0;
using T = int;

struct Point {
	T x, y;
	Point() {}
	Point(T a, T b) {x = a; y = b;}	
	Point operator+(const Point& other) const {
		return Point(x + other.x, y + other.y);
	}
	Point operator-(const Point& other) const {
		return Point(x - other.x, y - other.y);
	}
	T dot(const Point& other) const {
		return x * other.x + y * other.y;
	}
	double len() const {return sqrt(x * x + y * y);}
	// Length squared
	T len2() {return x*x + y*y;}
	double dist(const Point& other) const {
		T diffx = x - other.x; 
		T diffy = y - other.y;
		return sqrt(diffx*diffx + diffy*diffy);
	}
	double angle(const Point& other) const {
		return acos(dot(other) / len() / other.len());
	}
	Point scale(double d) const { return Point(d*x, d*y); }
	T cross(const Point& other) const {return x * other.y - other.x * y;}
};
using Vector = Point;

double angle(const Point& origin, const Point& p, const Point& q) {
	return (p - origin).angle(q - origin);
}

// | U x V | < 0 iff theta < pi
// | U x V | = 0 iff theta = pi
// | U x V | > 0 iff theta > pi

double area(const Point& origin, const Point& p, const Point& q) {
	return (p - origin).cross(q - origin);
}

bool collinear(const Point& a, const Point& b, const Point& c) {
	return -EPS < area(b, a, c) && area(b, a, c) < EPS;
}

bool ccw(const Point& a, const Point& b, const Point& c) {
	return area(b, c, a) > EPS;
}

bool cw(const Point& a, const Point& b, const Point& c) {
	return area(b, c, a) < -EPS;
}

double triangleArea(const Point& origin, const Point& p, const Point& q) {
	return area(origin, p, q) / 2;
}

struct LineSegment {
	Point start, end;
	LineSegment(Point p1, Point p2) {
		start = p1;
		end = p2;
	}
	double len() const {return start.dist(end);}
	// Length Squared
	T len2() const {return (end - start).len2();}
	Point closestPoint(const Point& other) const {		
		if ((end - start).dot(other - end) > 0) return end;
		if ((start - end).dot(other - start) > 0) return start;
		double t = (other - start).dot(end - start) / len2();
		return start + (end - start).scale(t);
	}
};

struct Circle {
	Point middle;
	double radius;
	Circle(Point p, double r) {middle = p; radius = r;}
	bool overlaps(const Circle& other) const {
		return other.radius + radius > middle.dist(other.middle);
	}
	double area() const { return PI * radius * radius; }
};
