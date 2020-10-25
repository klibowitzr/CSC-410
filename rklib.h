#ifndef RKLIB_H
#define RKLIB_H
#include <string>
#include <vector>



struct point{
  friend class Vector;
public:
  GLdouble x;
  GLdouble y;
  GLdouble z=0;
  // Vector subpts(point);
  point operator-(const point& p){
    point ret;
    ret.x=this->x-p.x;
    ret.y=this->y-p.y;
    ret.z=this->z-p.z;
    return ret;
  }
  void print();
  void set(GLdouble, GLdouble, GLdouble);
// point();
//   point(GLdouble, GLdouble, GLdouble);
};



void drawngon(GLint sides, GLdouble radius, GLdouble cx, GLdouble cy);
void drawngonswirl(GLint sides, GLdouble radius, GLdouble cx, GLdouble cy);
void halfcirc(GLdouble radius,GLint theta, GLdouble x, GLdouble y, GLint fill);
void thirdcirc(GLdouble radius, GLint theta, GLdouble cx, GLdouble cy);
void arc(GLdouble radius, GLint theta, GLdouble range, GLdouble cx, GLdouble cy, GLint reverse, GLint push);
void yinyang(GLdouble radius, GLdouble cx, GLdouble cy);
void cardioid(GLint k, GLint xc, GLint yc);
void rosecurve(GLint k, GLint petals, GLint xc, GLint yc);
void archcurve(GLint k, GLint xc, GLint yc);
void rosette(GLint sides, GLint radius, GLdouble xc, GLdouble yc);
GLdouble radtodeg(GLdouble r);
GLdouble degtorad(GLdouble d);
void roundarch(GLdouble w, GLdouble h, GLdouble sw, GLdouble sh);
void pointedarch(GLdouble w, GLdouble h, GLdouble swidth, GLdouble sheight);
void ogeearch(GLdouble w, GLdouble h, GLdouble swidth, GLdouble sheight);
void circle(GLdouble radius, GLdouble cx, GLdouble cy, GLint fill);

class polyline{
public:
  polyline();
  polyline(std::string filename);
  void draw();
  std::vector<point>ppoints;
};

class polydrawing{
public:
  polydrawing();
  // polydrawing(std::string filename);
  // void init();
  void init(std::string filename);
  void draw();
  void drawf();
  GLdouble getxmax();
  GLdouble getxmin();
  GLdouble getymin();
  GLdouble getymax();
  void world();
private:
  GLdouble xmin, ymin, xmax, ymax;
  GLdouble xscale, yscale;
};

// struct Vect{
//   GLdouble x;
//   GLdouble y;
//   GLdouble z;
// };

class Vector{
  friend struct point;
public:
  Vector(GLdouble,GLdouble,GLdouble);
  Vector(GLdouble,GLdouble);
  Vector();
  // void operator=(const Vector&);
  Vector add(Vector);
  point add(point);
  Vector sub(Vector);
  Vector cross(Vector);
  GLdouble dot(Vector);
  GLdouble mag();
  void normalize();
  void print();
  Vector subpts(point);
  GLdouble agbet(Vector);
  Vector perp();
  point vectptadd(point);
  Vector mult(GLdouble);
  GLdouble getx();
  GLdouble gety();
  GLdouble getz();
private:
  GLdouble x;
  GLdouble y;
  GLdouble z;
};
// void circl3(GLdouble& radiusvar, point& center, Vector a, Vector b, Vector c, point A);
// void idle(GLdouble& t);
struct Verts{
  friend struct Face;
public:
    Verts();
    Verts(std::vector<point> init);
    void populate();
  private:

};
struct Face{
  friend struct Verts;
public:
  // Face();
  Face(std::vector<point> init);
  std::vector<point> FaceVerts;
  std::vector<Vector> FaceNorms;
};
struct Mesh{
public:
    Mesh(std::vector<Face> init);
    Mesh();
    void init(std::string fname);
    void draw();
    // std::vector<point> verts;
    // std::vector<Vector> norms;
    std::vector<Face> faces;
};
#endif
