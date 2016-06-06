// GENERAL CASE FOR POLYGON COLLISIONS
// cumulative density would be awesome to see
// 03-FEB-2005

#define RENDER_VECTORS
#define PLOT_DENSITY
#define PERSIST_ARRAY
#define RENDER
//#define TRACE_ONE_POINT 

#define VARROWSCALE 30
#define AARROWSCALE 5000
#define DeLaY 1

#define TERMINAL_VELOCITY 1.0 

#include <cmath>
#include <iostream>
#include <vector>
#include <plot.h>
#include <cstdio>
#include <cstdlib>

#include <unistd.h>

using namespace std;

typedef float real_t;

const real_t pi = 3.1415926;
const real_t Q = 1.1;
const real_t radius = 10;

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
  point_t operator*(real_t a) const
    {
      return point_t(a * x, a * y);
    }
  point_t operator*(const point_t& p) const
    {
      return point_t(x * p.x, y * p.y);
    }
  point_t operator/(const real_t r) const
    {
      return point_t(x / r, y / r);
    }
};

typedef point_t vector_t;

struct particle_t 
{
  particle_t(point_t p1) { p = p1; }
  point_t  p; // position
  vector_t  v; // velocity
  vector_t  a; // acceleartion
  real_t    q; // charge 
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


typedef vector<particle_t> plist_t;
typedef vector<vector_t> vlist_t;

struct particle_system_t
{
  plist_t list;
  vector_t sum_forces(int i);
  plist_t::size_type size(void) { return list.size(); };
};

vector_t
particle_system_t::sum_forces(int pi)
{
  vector_t v(0, 0);
  real_t r;
  real_t F;
  vector_t dv;
  for (int i = 0; i < list.size(); ++i) 
    {
      if (i == pi)
        continue;
      else 
        {
          r = point_to_point_distance(list[pi].p, list[i].p);
          F = Q / (r * r);
          dv = list[pi].p - list[i].p;
          dv = dv / r;
          v.x += F * dv.x;
          v.y += F * dv.y;
        }
    }
  return vector_t(v.x, v.y);
}

real_t
rand_real(real_t l, real_t r)
{
  real_t diff = r - l;
  real_t res =  (((real_t)rand() / (real_t)RAND_MAX) * diff) + l;
  return res;
}

      float c=0;

void
delay(void)
{
      for (int a = 0; a < DeLaY; ++a)
        for (int b = 0; b < 1000; ++b)
          c = c * 2 / 1.8 + ( c / 10);
}
int
main(int argc, char *argv[])
{
  particle_system_t ps;
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

  pl_parampl("BITMAPSIZE", (void*)"500x500");
  pl_parampl("VANISH_ON_DELETE", (void*)"yes");
#ifndef TRACE_ONE_POINT
  pl_parampl("USE_DOUBLE_BUFFERING", (void*)"yes");
#endif

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

  pl_space(0, 0, 499, 499);
  pl_linewidth(1);
  pl_filltype(1);
  pl_bgcolorname("white");

#if 1
  while (count--)
    ps.list.push_back(point_t(rand_real(200, 299), rand_real(200, 299)));
#else
  ps.list.push_back(point_t(230, 250));
  ps.list.push_back(point_t(300, 200));
  ps.list.push_back(point_t(330, 350));
  ps.list.push_back(point_t(300, 300));
  ps.list.push_back(point_t(302, 320));
  ps.list.push_back(point_t(202, 320));

#endif
  int i;
  int m;

#ifdef TRACE_ONE_POINT
  pl_linewidth(0);
  pl_erase();
  pl_fillcolorname("black");
  pl_box(0, 0, 499, 499);
#endif

#ifdef PERSIST_ARRAY
  unsigned pmax(0);
  unsigned long persist_array[50][50];
  for (int x = 0; x < 10; ++x)
      for (int y = 0; y < 10; ++y)
          persist_array[x][y] = 0;
#endif

  for (m = 0; m < iter; ++m) {

#ifndef TRACE_ONE_POINT
    pl_erase();
#endif

#ifdef PLOT_DENSITY
    int carray[50][50];

    for (int x = 0; x < 10; ++x)
        for (int y = 0; y < 10; ++y)
           carray[x][y] = 0;

    int max = 0;
    for (i = 0; i < ps.size(); ++i)
      {
        int xc, yc;
        xc = (int)ps.list[i].p.x / 50;
        yc = (int)ps.list[i].p.y / 50;
        carray[xc][yc] += 1;
        max = carray[xc][yc] > max ? carray[xc][yc] : max;

#ifdef PERSIST_ARRAY
        persist_array[xc][yc] += 1;
        pmax = persist_array[xc][yc] > pmax ? persist_array[xc][yc] : pmax;
//        cout << pmax << endl;
#endif

      }

#ifdef PERSIST_ARRY
    for (int x = 0, xc = 0; x < 500; x +=500/10, ++xc )
      {
        for (int y = 0, yc = 0; y < 500; y += 500/10, ++yc)
          {
            float ratio = (float)persist_array[xc][yc] / (float)pmax;
            int color = (int)(65535.0f * ratio);
            pl_fillcolor(color,color,color);
            pl_box(x, y, x+50, y+50);
          }
      }
#else
    for (int x = 0, xc = 0; x < 500; x +=500/10, ++xc )
      {
        for (int y = 0, yc = 0; y < 500; y += 500/10, ++yc)
          {
            float ratio = (float)carray[xc][yc] / (float)max;
            int color = (int)(65535.0f * ratio);
            pl_fillcolor(color,color,color);
            pl_box(x, y, x+50, y+50);
          }
      }
#endif
#endif

    // Render
#ifdef RENDER
    for (i = 0; i < ps.size(); ++i)
      {
        point_t p;
        vector_t v, a;
        p = ps.list[i].p;
        v = ps.list[i].v;
        a = ps.list[i].a;
        if (p.x < -10 or p.x > 510 or
            p.y < -10 or p.y > 510)
          continue; 
#ifdef RENDER_VECTORS
        pl_pencolorname("red"); pl_linewidth(3);
        pl_line(p.x, p.y, p.x + v.x * VARROWSCALE, p.y + v.y * VARROWSCALE);
        pl_pencolorname("blue"); pl_linewidth(2);
        pl_line(p.x, p.y, p.x + a.x * AARROWSCALE, p.y + a.y * AARROWSCALE);
#endif
#ifdef TRACE_ONE_POINT
        if (i == 1) 
          {
        pl_pencolorname("red"); pl_linewidth(1);
        pl_line(p.x, p.y, p.x + v.x * VARROWSCALE, p.y + v.y * VARROWSCALE);
        pl_pencolorname("blue"); pl_linewidth(1);
        pl_line(p.x, p.y, p.x + a.x * AARROWSCALE, p.y + a.y * AARROWSCALE);
/*
            pl_pencolorname("white");
            pl_linewidth(0);
            //pl_point(p.x, p.y);
            float r;
//            float r= point_to_point_distance(ps.list[i].a);
//            r = r * 1000;
//            pl_circle(p.x, p.y, r);
            pl_point(p.x, p.y);
*/
          }
#else
        pl_pencolorname("black");
        pl_linewidth(1);
        pl_circle(p.x, p.y, 2);
#endif
     
      }
#endif           
    // 1. Computer forces on all particles (they are idle and inertial)
    for (i = 0; i < ps.size(); ++i) 
      {
        // Compute acceleration on all particles
        // a = F * ?
        ps.list[i].a = ps.sum_forces(i);

        // one tick = one second = one time unit
        ps.list[i].v = ps.list[i].v + ps.list[i].a;
#if 1
        real_t magv;
        magv = point_to_point_distance(ps.list[i].v);
        // terminal velocity
        if (magv > TERMINAL_VELOCITY)
          {
            real_t scale = 1.0 - (TERMINAL_VELOCITY / magv);
            ps.list[i].v = ps.list[i].v * scale;
          }
#endif

        ps.list[i].p = ps.list[i].p + ps.list[i].v;
        if (ps.list[i].p.x < 0)
          {
            ps.list[i].p.x = -ps.list[i].p.x;
            ps.list[i].v.x = -ps.list[i].v.x;
          }
        if (ps.list[i].p.x > 500)
          {
            ps.list[i].p.x = 500 - (ps.list[i].p.x - 500);
            ps.list[i].v.x = -ps.list[i].v.x;
          }
        if (ps.list[i].p.y < 0)
          {
            ps.list[i].p.y = -ps.list[i].p.y;
            ps.list[i].v.y = -ps.list[i].v.y;
          }
        if (ps.list[i].p.y > 500)
          {
            ps.list[i].p.y = 500 - (ps.list[i].p.y - 500);
            ps.list[i].v.y = -ps.list[i].v.y;
          }
      } 

    // 2. can we move w/o a collision?

//    delay();
    
  }

  sleep(65000000);

  pl_closepl();
  pl_selectpl(0);
  pl_deletepl(handle);

  return 0;
}

