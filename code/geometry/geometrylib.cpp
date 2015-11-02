#include <cmath>
using namespace std;
const double EPS = 0.0000001;
const double TAU = 6.28318530717958647692528;
const double PI = TAU/2.0;
using T = int;
/* 
template <class T>
struct Point {
	typedef T coordType;
	typedef Point P;
	typedef const P & R;
	T x, y;
	explicit Point(T x=T(), T y=T()) : x( x), y( y) { }
	bool operator<(R p) const { return x<p.x || x==p.x && y<p.y; }
	bool operator==(R p) const { return x==p.x && y==p.y; }
	P operator+(R p) const { return P(x+p.x, y+p.y); }
	P operator-(R p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(R p) const { return x*p.x + y*p.y; }
	T cross(R p) const { return x*p.y - y*p.x; }
	T dist2() const { return x*x + y*y; } //distance^2
	double dist() const { return sqrt((double)dist2()); } //length
	//angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	P perp() const { return P(-y, x); } //rotates +pi/2 radians
	P normal() const { return perp().unit(); }
	//returns point rotated a radians counterclockwise around origo
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));
	}
};


*/
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
