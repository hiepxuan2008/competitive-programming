// Problem: Basic Geometry
// Author: BigO & Mai Thanh Hiep

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
typedef long long ll;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const double EPS = 1e-9;

int cmp(double x, double y) {
    return (x < y + EPS) ? -1 : (x > y + EPS);
}

struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    int cmp(const Point &p) const {
        if (x != p.x) return ::cmp(x, p.x);
        return ::cmp(y, p.y);
    }

#define op(x) bool operator x (const Point& p) const { return cmp(p) x 0;}

    op(>)

    op(<)

    op(==)

    op(>=)

    op(<=)

    op(!=)

#undef op

    Point operator+(const Point &p) const {
        return {x + p.x, y + p.y};
    }

    Point operator-(const Point &p) const {
        return {x - p.x, y - p.y};
    }

    Point operator*(double k) const {
        return {x * k, y * k};
    }

    Point operator/(double k) const {
        return {x / k, y / k};
    }

    // dot product
    double dot(const Point &p) const {
        return x * p.x + y * p.y;
    }

    // cross product
    double cross(const Point &p) const {
        return x * p.y - y * p.x;
    }

    double norm() {
        return x * x + y * y;
    }

    double len() {
        return sqrt(norm());
    }

    Point rotate(double alpha) const {
        double cosa = cos(alpha), sina = sin(alpha);
        return {x * cosa - y * sina, x * sina + y * cosa};
    }
};

struct Line {
    double a, b, c;
    Point A, B;

    Line(double a, double b, double c) : a(a), b(b), c(c) {}

    Line(const Point &A, const Point &B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }

    Line(Point P, double k) {
        a = -k;
        b = 1;
        c = k * P.x - P.y;
    }

    double f(const Point &A) {
        return a * A.x + b * A.y + c;
    }

    bool areParallel(const Line &l1, const Line &l2) {
        return cmp(l1.a * l2.b, l1.b * l2.a) == 0;
    }

    bool areSame(const Line &l1, const Line &l2) {
        return areParallel(l1, l2) && cmp(l1.c * l2.a, l2.c * l1.a) == 0 && cmp(l1.c * l2.b, l1.b * l2.c) == 0;
    }

    bool areIntersect(const Line &l1, const Line &l2, Point &outPoint) {
        if (areParallel(l1, l2)) return false;
        double dx = l1.b * l2.c - l2.b * l1.c;
        double dy = l1.c * l2.a - l2.c * l1.a;
        double d = l1.a * l2.b - l2.a * l1.b;
        outPoint = Point(dx / d, dy / d);
        return true;
    }

    double distToLine(const Point &p, const Point &a, const Point &b, Point &outPoint) {
        Point ap = p - a, ab = b - a;
        double k = ap.dot(ab) / ab.norm();
        outPoint = a + (ab * k);
        return (p - outPoint).len();
    }
};

struct Circle : Point {
    double r;

    Circle(double x = 0, double y = 0, double r = 0) : Point(x, y), r(r) {}

    Circle(const Point& p, double r) : Point(p), r(r) {}

    bool contains(const Point& p) {
        return (*this - p).len() <= r + EPS;
    }

    vector<Point> intersection(const Line& l, const Circle& cir) {
        double r = cir.r;
        double a = l.a, b = l.b, c = l.c + l.a * cir.x + l.b * cir.y;
        vector<Point> res;

        double x0 = -a * c / (a*a + b*b);
        double y0 = -b * c / (a*a + b*b);

        if (c*c > r*r*(a*a + b*b) + EPS)
            return res;
        if (fabs(c*c - r*r*(a*a+b*b)) < EPS) {
            res.push_back(Point(x0, y0) + Point(cir.x, cir.y));
            return res;
        }
        double d = r * r - c * c / (a*a + b* b);
        double mult = sqrt(d / (a*a + b * b));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        res.push_back(Point(ax, ay) + Point(cir.x, cir.y));
        res.push_back(Point(bx, by) + Point(cir.x, cir.y));
        return res;
    }
};

int main() {
    //    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}