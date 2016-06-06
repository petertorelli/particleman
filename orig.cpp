// GENERAL CASE FOR POLYGON COLLISIONS

#include <cmath>
#include <iostream>
#include <vector>
#include <plot.h>
#include <unistd.h>
#include <curses.h>

using namespace std;

typedef float real_t;

const real_t pi = 3.1415926;
const real_t Q = 100;
const real_t radius = 1;

struct point_t
{
  real_t x, y;
  point_t() { x = y = 0; }
  point_t(real_t _x, real_t _y) { x = _x; y= _y; }
  point_t operator+(const point_t& p) const
    {
      return point_t(x + p.x, y + p.y);
    }
  point_t operator-(const point_t& p) const
    {
      return point_t(x - p.x, y - p.y);
    }
  point_t operator/(const real_t r) const
    {
      return point_t(x / r, y / r);
    }
};

ostream&
operator<<(ostream& os, const point_t& p)
{
  return os << p.x << "," << p.y;
}

real_t
point_to_point_distance(const point_t& p1, const point_t& p2)
{
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

real_t
point_to_point_distance(const point_t& p1)
{
  return sqrt(pow(p1.x, 2) + pow(p1.y, 2));
}

struct edge_t 
{
  edge_t(point_t a, point_t b) {p1 = a; p2 = b;}
  point_t p1, p2;
  // Does this get optimized to an fmul x,x?
  real_t length() { return point_to_point_distance(p1, p2); }
};

static real_t
angle(const edge_t& e, const point_t& p)
{
  point_t p1, p2;
  real_t a1, a2;
  // Translate so that e.p1 = origin
  p1 = e.p2 - e.p1;
  p2 = p - e.p1;
  // At O(), the angles are the inverse tangent
  a1 = static_cast<real_t>(atan(p1.y / p1.x));
  a2 = static_cast<real_t>(atan(p2.y / p2.x));
  // is fabs() faster?
  return (a1 > a2) ? a1 - a2 : a2 - a1;
}

static real_t
rad2deg(real_t r)
{
  return r * 180.0 / pi;
}

static real_t
point_to_edge_distance(const point_t& p, const edge_t& e)
{
  edge_t CB(e.p1, p);
  return CB.length() * sin(angle(e, p));
}


typedef vector<point_t> plist_t;

struct point_structure_t
{
  plist_t list;
  point_t force_on_pt(int i);
  plist_t::size_type size(void) { return list.size(); };
};

point_t
point_structure_t::force_on_pt(int pi)
{
  point_t v(0, 0);
  real_t r;
  real_t F;
  point_t dv;
  for (int i = 0; i < list.size(); ++i) 
    {
      if (i == pi)
        continue;
      else 
        {
          r = point_to_point_distance(list[pi], list[i]);
          F = Q / (r * r);
          dv = list[pi] - list[i];
          dv = dv / r;
          v.x += F * dv.x;
          v.y += F * dv.y;
        }
    }
  return point_t(v.x, v.y);
}

real_t
rand_real(real_t l, real_t r)
{
  real_t diff = r - l;
  real_t res =  (((real_t)rand() / (real_t)RAND_MAX) * diff) + l;
  cout << res << endl;
  return res;
}

int
main(int argc, char *argv[])
{
  point_structure_t ps;
  int iter;

  int count = 5;

  if (argc > 1) 
    iter = atoi(argv[1]);
  if (argc > 2) 
    count = atoi(argv[2]);
  if (argc > 3) 
    srand(atoi(argv[3]));
  

  edge_t N(point_t(  0, 100), point_t(100, 100));
  edge_t S(point_t(  0,   0), point_t(100,   0));
  edge_t E(point_t(  0,   0), point_t(  0, 100));
  edge_t W(point_t(100,   0), point_t(100, 100));

  int handle;

  pl_parampl ("BITMAPSIZE", "200x200");
  pl_parampl ("VANISH_ON_DELETE", "yes");
  pl_parampl ("USE_DOUBLE_BUFFERING", "yes");

  if((handle = pl_newpl("X", stdin, stdout, stderr)) < 0)
    {
      cout << "Failed to initialize plotter\n";
      return 1;
    }

  pl_selectpl(handle);

  if (pl_openpl() < 0)
    {
      cout << "Failed to open plotter\n";
      return 1;
    }

  pl_space(0, 0, 199, 199);
  pl_linewidth(1);
  pl_filltype(1);
  pl_bgcolorname("white");

  while (count--)
    ps.list.push_back(point_t(rand_real(0, 199), rand_real(0, 199)));

  for (int m = 0; m < iter; ++m) {

      plist_t dir;
      plist_t moved;
      plist_t final;

      for (int i = 0; i < ps.size(); ++i)
        {
          point_t fv = ps.force_on_pt(i);
          dir.push_back(fv);
          real_t f = point_to_point_distance(fv);
        }

      for (int i = 0; i < dir.size(); ++i) 
        {
          // basically, ignoring velocity, move the points one step in the
          // force vector direction until they hit a wall in x/y or another
          // point in x/y...  velocity would require a new class w/history
          moved.push_back(dir[i] + ps.list[i]);
        }

      final.resize(moved.size());
    
      for (int i = 0; i < moved.size(); ++i)
        {
          // check for collisions with each other.  Simple collisions: touch=
          // lose all motion
          for (int j = 0; j < moved.size(); ++j)
            {
              if (i == j)
                continue;
              if (radius > point_to_point_distance(moved[i], moved[j]))
                {
                  final[i] = ps.list[i];
                  break;
                }
              else
                final[i] = moved[i];
            }
        }
    
//      ps.list = final;
      ps.list = moved;


      pl_erase();
      for (int i = 0; i < final.size(); ++i)
        {
          //cout << i << " : " << final[i] << endl;
          pl_colorname("black");
          pl_circle(final[i].x, final[i].y, 2);
        }
      float c=0;
      for (int a = 0; a < 100; ++a)
        for (int b = 0; b < 1000; ++b)
          c = c * 2 / 1.8 + ( c / 10);
    }

  while (getch() != ERR) {}

  pl_closepl();
  pl_selectpl(0);
  pl_deletepl(handle);

  return 0;
}

