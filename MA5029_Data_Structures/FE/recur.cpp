#include <iostream>

using namespace std;

class Point {
  private :
    double x, y;

  public :
    Point () : x (0), y (0) {}
    Point (const double& a, const double& b) : x (a), y (b) {}
    friend Point operator+ (const Point& a, const Point& b) { return Point (a.x + b.x, a.y + b.y); }
   
    Point& operator/ (const double& n) {
      x /= n;
      y /= n;
      return *this;
    }

    friend ostream& operator<< (ostream& out, const Point& src) {
      cout << src.x << ' ' << src.y << endl;
      return out;
    }
};

class Quadrangle {
  private :
    Point ang[4];

  public :
    Quadrangle (const Point& a, const Point& b, const Point& c, const Point& d) {
      ang[0] = a;
      ang[1] = b;
      ang[2] = c;
      ang[3] = d;
    }
    Point operator[] (const int& n) { return ang[n]; }
    friend ostream& operator<< (ostream& out, const Quadrangle& src) {
      for (int i = 0; i < 4; ++ i) { cout << src.ang[i]; }
      cout << endl;
      return out;
    }
};

void generate_grids (int m, Quadrangle foo) {
  if (m == 1) {
    cout << foo << endl;
  } else {
    Point pt1, pt2, pt3, pt4, pt5;
    pt1 = (foo[0] + foo[1]) / 2.;
    pt2 = (foo[1] + foo[2]) / 2.;
    pt3 = (foo[2] + foo[3]) / 2.;
    pt4 = (foo[3] + foo[0]) / 2.;
    pt5 = (foo[0] + foo[1] + foo[2] + foo[3]) / 4.;
    cout << pt1 << pt2 << pt3 << pt4 << pt5;

    cout << foo << endl;

    generate_grids (m - 1, Quadrangle (foo[3], pt4, pt5, pt3));
    generate_grids (m - 1, Quadrangle (foo[0], pt1, pt5, pt4));
  }
}

int main () {
  Quadrangle foo (Point(0, 0), Point (2, 0), Point (1, 2), Point (0, 1));
  generate_grids (5, foo);
  return 0;
}
