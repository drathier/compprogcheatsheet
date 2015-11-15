#include <vector>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const double EPS = 0.000000001;
const double TAU = 6.28318530717958647692528;
const double PI = TAU/2.0;
using T = double;

struct Point {
    T x, y;
    Point() {}
    Point(T a, T b) {x = a; y = b;} 
    Point operator+(const Point& rhs) const {return Point(x+rhs.x, y+rhs.y);}
    Point operator-(const Point& rhs) const {return Point(x-rhs.x, y-rhs.y);}
    Point operator*(T scalar) const {return Point(x*scalar, y*scalar);}
    Point operator/(T scalar) const {return Point(x/scalar, y/scalar);}
    T        dot(const Point& other) const {return x * other.x + y * other.y;}
    double   len() const {return sqrt(x * x + y * y);}
    // Length squared
    T        len2() const {return x*x + y*y;}
    double   angle() const { return atan2(y, x); }
    double   angle(const Point& other) const {return (other - *this).angle();}
    double   dist(const Point& other) const {return (other - *this).len();}
    T        cross(const Point& other) const {return x * other.y - other.x * y;}
    Point    unit() const { return *this / len(); }
    Point    rotate(double rad) const { return Point(cos(rad)*x-y*sin(rad), x*sin(rad)+y*cos(rad)); }
    Point    norm() const {return Point(-y, x).unit();}
};
using Vector = Point;

vector<double> compute_angles(vector<Point>& pts, int pivot) {
    vector<double> angles;
    for (int i = 0; i < (int) pts.size(); ++i) {
        if (i != pivot) angles.push_back(pts[pivot].angle(pts[i]));
    }
    sort(angles.begin(), angles.end());
    return angles;
}

int collinear_points(vector<Point>& pts) {
    if ((int) pts.size() == 1) return 1;

    int found_points = 0;
    for (int pivot = 0; pivot < (int) pts.size(); ++pivot) {
        vector<double> angles = compute_angles(pts, pivot);
        int best_streak = 1;
        int streak = 1;

        double last_angle = angles[0];
        for (int i = 1; i < (int) angles.size(); ++i) {
            double d = angles[i];
            if (abs(last_angle - d) < EPS) {
                streak++;
                best_streak = best_streak > streak ? best_streak : streak;
            } else {
                streak = 1;
                last_angle = d;
            }
        }
        best_streak++;
        found_points = best_streak > found_points ? best_streak : found_points;
    }
    return found_points;
}
