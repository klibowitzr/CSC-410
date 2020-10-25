#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"
#include <fstream>
// #include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>


std::vector<point> points;
std::vector<GLint> lines;
std::vector<GLint>::iterator it;
// std::fstream fin;
void point::set(GLdouble xx, GLdouble yy, GLdouble  zz){
  x=xx;
  y=yy;
  z=zz;
}

polyline::polyline(std::string filename){
  std::fstream fin;
  fin.open(filename, std::ios::in);
  if(fin.fail()){
    std::cout << filename << " failed to open." << std::endl;
    exit(0);
  }
  GLdouble numpolys,  numLines, x, y;
  point p;
    fin >>numLines;
    for(int i=0; i<numLines; i++){
      fin >> x >>  y;
      p.x=x;
      p.y=y;
      ppoints.push_back(p);
    }
  fin.close();
}

void polyline::draw(){
  glBegin(GL_LINE_STRIP);
  for(GLint i=0; i<ppoints.size(); i++){
    glVertex2d(ppoints[i].x, ppoints[i].y);
  }
  glEnd();
}
polydrawing::polydrawing(){

}
void polydrawing::init(std::string filename){
  std::fstream fin;
  fin.open(filename, std::ios::in);
  if(fin.fail()){
    std::cout << filename << " failed to open." << std::endl;
    exit(0);
  }
  GLdouble numpolys, numLines, x, y;
  point p;
  GLint loc1, loc2;
  fin.seekg(0);
  std::string c;
  getline(fin,c);
  // std::cout << "C: " << c << std::endl;
  if(isdigit(c[0])){
    // std::cout << "In for loop" << std::endl;
    GLint firstround=1;
    fin.seekg(0);
    fin >> numpolys;
    // std::cout << "NUMOFPOLYS: " << numpolys << std::endl;
    for(GLint i=0; i<numpolys; i++){
      fin >> numLines;
      // std::cout << "NUMOFLINES: " << numLines << std::endl;
      lines.push_back(numLines);
      for(GLint j=0; j<numLines; j++){
        fin >> x >> y;
        p.x=x;
        p.y=y;
        points.push_back(p);
        if(firstround==1){
          xmin=xmax=x;
          ymin=ymax=y;
          firstround=0;
        }
        else{
          if(x>xmax) xmax=x;
          if(x<xmin) xmin=x;
          if(y>ymax) ymax=y;
          if(y<ymin) ymin=y;
        }
      }
    }
    // setWorldWin(xmin,xmax,ymin,ymax);
  }
  else{
    // std::cout << "In else loop" << std::endl;
    do{
      loc2=fin.tellg();
      getline(fin,c);
    }
    while(!isdigit(c[0]));
    fin.seekg(loc2, std::ios_base::beg);
    fin >> xmin >> ymax >> xmax >>ymin;
    fin >> numpolys;
     for(int i=0; i<numpolys; i++){
       // std::cout << "NUMOFPOLYS: " << numpolys << std::endl;
         fin >>numLines;
         // std::cout << "NUMOFLINES: " << numLines << std::endl;
         lines.push_back(numLines);
         for(int i=0; i<numLines; i++){
           fin >> x >>  y;
           p.x=x;
           p.y=y;
           // std::cout << "X: " << x << " Y: " << y << std::endl;
           points.push_back(p);
         }
       }
       // setWorldWin(xmin,xmax,ymin,ymax);
  }
  fin.close();
}
GLdouble polydrawing::getxmax(){
  return xmax;
}
GLdouble polydrawing::getxmin(){
  return xmin;
}
GLdouble polydrawing::getymax(){
  return ymax;
}
GLdouble polydrawing::getymin(){
  return ymin;
}
void polydrawing::world(){
  setWorldWin(xmin,xmax,ymin,ymax);
}
void polydrawing::draw(){
  GLint a;
  GLint iterator=0;
  // setWorldWin(xmin,xmax,ymin,ymax);

  for(it=lines.begin(); it!=lines.end(); ++it){
    a=(*it);
    glBegin(GL_LINE_STRIP);
    for(GLint i=0; i<a; i++){
      glVertex2d(points[iterator].x, points[iterator].y);
      iterator++;
    }
    glEnd();
  }
}

GLdouble radtodeg(GLdouble r){
  return (r*180.0)/M_PI;
}

GLdouble degtorad(GLdouble d){
  return (d*M_PI)/180.0;
}

void drawngon(GLint sides, GLdouble radius, GLdouble cx, GLdouble cy){
  // std::cout << "Calling from inside drawngon before glBegin with gl line loop" << std::endl;
  GLdouble t=360.0/sides;
  glBegin(GL_LINE_LOOP);
  GLdouble x, y, nx, ny, theta;
  theta=t;
  // std::cout << "Calling from inside drawngon after glBegin" << std::endl
  for(GLint i=0; i<sides; i++){
    nx=(radius*cos(degtorad(theta))+cx);
    ny=(radius*sin(degtorad(theta))+cy);
    glVertex2d(nx,ny);
    std::cout << nx << " " << ny << std::endl;
    theta+=t;
  }
  glEnd();
}


void drawngonswirl(GLint sides, GLdouble radius, GLdouble cx, GLdouble cy){
  GLdouble t=360/sides;
  GLdouble x, y, nx, ny, theta,  swirl;
  swirl=sides;
  GLint i,  j;
  for (j=1; j<=radius*2.5; j++){
    for(i=0; i<sides; i++){
      glBegin(GL_LINE_LOOP);
      nx=(radius*cos(degtorad(theta))+cx);
      ny=(radius*sin(degtorad(theta))+cy);
      glVertex2d(nx,ny);
      theta+=t;
    }
    glEnd();
    theta=t+(j*swirl);
    radius=radius-(1.7*swirl);
  }
}

void halfcirc(GLdouble radius,GLint theta, GLdouble cx, GLdouble cy, GLint fill){
  if(fill==0){
    glBegin(GL_LINE_STRIP);
    GLdouble x, y, nx, ny, t;
    for(t=theta; t<=theta+180;t++){
      nx=(radius*cos(degtorad(t))+cx);
      ny=(radius*sin(degtorad(t))+cy);
      glVertex2d(nx,ny);
    }
    glEnd();
  }
  else{
    glBegin(GL_POLYGON);
    GLdouble x, y, nx, ny, t;
    for(t=theta; t<=theta+180;t++){
      nx=(radius*cos(degtorad(t))+cx);
      ny=(radius*sin(degtorad(t))+cy);
      glVertex2d(nx,ny);
    }
    glEnd();
  }
}

void thirdcirc(GLdouble radius, GLint theta, GLdouble cx, GLdouble cy, GLint reverse){
  if(reverse==0){
    glBegin(GL_LINE_STRIP);
    GLdouble x, y, nx, ny, t;
    for(t=theta; t<=theta+60; t++){
      nx=(radius*cos(degtorad(t))+cx);
      ny=(radius*sin(degtorad(t))+cy);
      glVertex2d(nx,ny);
    }
    glEnd();
  }
  if(reverse==1){
    glBegin(GL_LINE_STRIP);
    GLdouble x, y, nx, ny, t;
    for(t=theta; t>=theta-60; t--){
      nx=(radius*cos(degtorad(t))+cx);
      ny=(radius*sin(degtorad(t))+cy);
      glVertex2d(nx,ny);
    }
    glEnd();
  }
}
void arc(GLdouble radius, GLint theta, GLdouble range, GLdouble cx, GLdouble cy, GLint reverse, GLint push){
  point p;
  if(reverse==0){
    if(push==0){
      glBegin(GL_LINE_STRIP);
      GLdouble x, y, nx, ny, t;
      for(t=theta; t<=theta+range; t++){
        nx=(radius*cos(degtorad(t))+cx);
        ny=(radius*sin(degtorad(t))+cy);
        glVertex2d(nx,ny);
        // std::cout << nx << ", " << ny << std::endl;
      }
      glEnd();
    }
    else{
      // glBegin(GL_LINE_STRIP);
      GLdouble x, y, nx, ny, t;
      for(t=theta; t<=theta+range; t++){
        nx=(radius*cos(degtorad(t))+cx);
        ny=(radius*sin(degtorad(t))+cy);
        glVertex2d(nx,ny);
        // std::cout << nx << ", " << ny << std::endl;
        p.x=nx;
        p.y=ny;
        points.push_back(p);
      }
    }

  }
  if(reverse==1){
    if(push==0){
      glBegin(GL_LINE_STRIP);
      GLdouble x, y, nx, ny, t;
      for(t=theta; t>=theta-range; t--){
        nx=(radius*cos(degtorad(t))+cx);
        ny=(radius*sin(degtorad(t))+cy);
        glVertex2d(nx,ny);
        // std::cout << nx << ", " << ny << std::endl;
      }
      glEnd();
    }
    else{
      // glBegin(GL_LINE_STRIP);
      GLdouble x, y, nx, ny, t;
      for(t=theta; t>=theta-range; t--){
        nx=(radius*cos(degtorad(t))+cx);
        ny=(radius*sin(degtorad(t))+cy);
        glVertex2d(nx,ny);
        // std::cout << nx << ", " << ny << std::endl;
        p.x=nx;
        p.y=ny;
        points.push_back(p);
      }
    }

}
}

void circle(GLdouble radius, GLdouble cx, GLdouble cy, GLint fill){
  if(fill==0){
    glBegin(GL_LINE_STRIP);
    GLdouble x, y, nx, ny, theta;
    theta=0;
    for(GLint i=0; i<=360; i++){
      nx=(radius*cos(degtorad(theta))+cx);
      ny=(radius*sin(degtorad(theta))+cy);
      glVertex2d(nx,ny);
      theta++;
    }
    glEnd();
  }
  else{
    glBegin(GL_POLYGON);
    GLdouble x, y, nx, ny, theta;
    theta=0;
    for(GLint i=0; i<360; i++){
      nx=(radius*cos(degtorad(theta))+cx);
      ny=(radius*sin(degtorad(theta))+cy);
      glVertex2d(nx,ny);
      theta++;
    }
    glEnd();
  }
}

void yinyang(GLdouble radius, GLdouble cx, GLdouble cy){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0, 0.0, 0.0);
  halfcirc(radius,0,cx,cy,1);
  halfcirc(radius,180,cx,cy,0);
  circle((radius/2), cx-(radius/2), cy, 1);
  glColor3f(1.0, 1.0, 1.0);
  circle((radius/2)-1, cx+(radius/2), cy, 1);
  circle(radius/8, cx-(radius/2), cy, 1);
  glColor3f(0.0, 0.0, 0.0);
  circle(radius/8, cx+(radius/2), cy, 1);
  halfcirc(radius/8,0,cx+(radius/2),cy,0);

}

void cardioid(GLint k, GLint xc, GLint yc){
  GLint theta;
  GLdouble r,t,x,y;
  glBegin(GL_LINE_LOOP);
  for(theta=0;theta<=360;theta++){
    t=theta;
    t=degtorad(t);
    r=k*(1+cos(t));
    x=r*cos(t)+xc;
    y=r*sin(t)+yc;
    glVertex2d(x,y);
  }
  glEnd();
}

void rosecurve(GLint k, GLint petals, GLint xc, GLint yc){
  GLint theta;
  GLdouble r,t,x,y;
  glBegin(GL_LINE_LOOP);
  for(theta=0;theta<=360;theta++){
    t=theta;
    t=degtorad(t);
    r=k*(cos(t*petals));
    x=r*cos(t)+xc;
    y=r*sin(t)+yc;
    glVertex2d(x,y);
  }
  glEnd();
}

void archcurve(GLint k, GLint xc, GLint yc){
  GLint theta;
  GLdouble r,t,x,y;
  glBegin(GL_LINE_STRIP);
  // for(theta=0;theta<=360;theta++){
  do{
    t=theta;
    t=degtorad(t);
    r=k*t;
    x=r*cos(t)+xc;
    y=r*sin(t)+yc;
    glVertex2d(x,y);
    theta++;
  }
  while(x<(xc*2)-20 && y<(yc*2)-20);
  glEnd();
}



void rosette(GLint sides, GLint radius, GLdouble cx, GLdouble cy){
  GLdouble t=360.0/sides;
  // std::cout << t << std::endl;
  glBegin(GL_LINE_LOOP);
  GLdouble x, y, nx, ny, theta;
  theta=0.0;
  for(GLint i=0; i<sides; i++){
    nx=(radius*cos(degtorad(theta))+cx);
    ny=(radius*sin(degtorad(theta))+cy);
    glVertex2d(nx,ny);
    point p;
    p.x=nx;
    p.y=ny;
    points.push_back(p);
    theta+=t;
  }
  glEnd();
  for(GLint i=0; i<points.size(); i++){
    for(GLint j=0; j<points.size(); j++){
      glBegin(GL_LINE_STRIP);
      glVertex2d(points[i].x, points[i].y);
      glVertex2d(points[j].x, points[j].y);
      glEnd();
    }
  }
  points.clear();
}

void roundarch(GLdouble w, GLdouble h, GLdouble swidth, GLdouble sheight){
  // halfcirc(w,0,swidth/2,h,0);
  w=w/2;
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  halfcirc(100,0,swidth/2.0,h,0);
  glBegin(GL_LINE_STRIP);
  glVertex2d(swidth/2+w,h);
  glVertex2d(swidth/2+w,0);
  glVertex2d(swidth/2-w,0);
  glVertex2d(swidth/2-w,h);
  glEnd();
}

void pointedarch(GLdouble w, GLdouble h, GLdouble swidth, GLdouble sheight){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  // thirdcirc(2*w,0, swidth/2-w,h,0);
  // thirdcirc(2*w,180,swidth/2+w,h,1);
  arc(w,0,60,swidth/2-w/2,h,0,1);
  arc(w,120,60,swidth/2+w/2,h,0,1);
  glBegin(GL_LINE_LOOP);
  for(GLint i=0; i<points.size(); i++){
    glVertex2d(points[i].x, points[i].y);
  }
  glVertex2d(swidth/2-w/2,h);
  glVertex2d(swidth/2-w/2,0);
  glVertex2d(swidth/2+w/2,0);
  glVertex2d(swidth/2+w/2,h);
  glEnd();
  points.clear();
}

void ogeearch(GLdouble w, GLdouble h, GLdouble swidth, GLdouble sheight){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  // arc(w/2,0,60,swidth/2.0,h,0,1);
  // arc(w/2,240,60,swidth/2.0+w/2.0, h+w*(7.0/8.0),1,1);
  // arc(w/2,360,60,swidth/2.0-w/2.0,h+w*(7.0/8.0),1,1);
  // arc(w/2,120,60,swidth/2.0,h,0,1);
  arc(w/2,0,60,swidth/2.0,h,0,1);
  arc(w/2,240,60,swidth/2.0+w/2, h+2*w/2*(7.0/8.0),1,1);
  arc(w/2,360,60,swidth/2.0-w/2,h+2*w/2*(7.0/8.0),1,1);
  arc(w/2,120,60,swidth/2.0,h,0,1);
  glBegin(GL_LINE_LOOP);
  for(GLint i=0; i<points.size(); i++){
    glVertex2d(points[i].x, points[i].y);
  }
  glVertex2d(swidth/2-w/2,h);
  glVertex2d(swidth/2-w/2,0);

  glVertex2d(swidth/2+w/2,0);
  glVertex2d(swidth/2+w/2,h);

  glEnd();
  points.clear();
}


Vector::Vector(GLdouble xx, GLdouble yy, GLdouble zz){
  x=xx;
  y=yy;
  z=zz;
}

Vector::Vector(GLdouble xx, GLdouble yy){
  x=xx;
  y=yy;
  z=0;
}

Vector::Vector(){
  x=0;
  y=0;
  z=0;
}

Vector Vector::cross(Vector b){
  Vector ret;
  ret.x=this->y*b.z-(this->z*b.y);
  ret.y=this->z*b.x-(this->x*b.z);
  ret.z=this->x*b.y-(this->y*b.x);
  return ret;
}

GLdouble Vector::dot(Vector b){
  GLdouble ret;
  ret=(this->x*b.x)+(this->y*b.y)+(this->z*b.z);
  return ret;
}

void Vector::print(){
  std::cout << "< " << this->x << ", " << this->y << ", " << this->z << " >" << std::endl;
}

Vector Vector::add(Vector b){
  Vector sum;
  sum.x=this->x+b.x;
  sum.y=this->y+b.y;
  sum.z=this->z+b.z;
  return sum;
}
point Vector::add(point p){
  point ret;
  ret.x=this->x+p.x;
  ret.y=this->y+p.y;
  ret.z=this->z+p.z;
  return ret;
}
Vector Vector::sub(Vector b){
  Vector diff;
  diff.x=this->x-b.x;
  diff.y=this->y-b.y;
  diff.z=this->z-b.z;
  return diff;
}
GLdouble Vector::mag(){
  GLdouble mag;
  mag=sqrt(pow(this->x,2)+pow(this->y,2)+pow(this->z,2));
  return mag;
}

void Vector::normalize(){
  GLdouble mag;
  mag=this->mag();
  // std::cout << "mag in normalize: " << mag << std::endl;
  this->x=(this->x)/mag;
  this->y=(this->y)/mag;
  this->z=(this->z)/mag;
}

Vector Vector::subpts(point p){
  Vector v;
  v.x=this->x-p.x;
  v.y=this->y-p.y;
  v.z=this->z-p.z;
  return v;
}

GLdouble Vector::agbet(Vector v){
  GLdouble numerator=this->dot(v);
  GLdouble mag1, mag2, denom, theta;
  mag1=this->mag();
  mag2=v.mag();
  denom=mag1 * mag2;
  theta=radtodeg(acos(degtorad(numerator/denom)));
  return theta;
}
Vector Vector::perp(){
    Vector ret;
    ret.x=this->y*-1;
    ret.y=this->x;
    ret.z=0;
    return ret;
}
point Vector::vectptadd(point b){
  point p;
  p.x=this->x+b.x;
  p.y=this->y+b.y;
  p.z=this->z+b.z;
  return p;
}
Vector Vector::mult(GLdouble x){
  Vector ret;
  ret.x=this->x*x;
  ret.y=this->y*x;
  ret.z=this->z*x;
  return ret;
}
GLdouble Vector::getx(){
  return x;
}
GLdouble Vector::gety(){
  return y;
}
GLdouble Vector::getz(){
  return z;
}
void point::print(){
  std::cout << "( " << x << ", " << y << ", " << z << ")" << std::endl;
}

void circl3(GLdouble& radiusvar , point& center, Vector a, Vector b, Vector c, point A){
  point S, temp, r;
  GLdouble  mult, radius;
  Vector aperp,d,e,f;

  aperp=a.perp();
  mult=(b.dot(c))/(aperp.dot(c));
  d=aperp.mult(mult);
  e=d.add(a);
  f=e.mult(.5);
  S=f.add(A);
  center=S;
  r=S-A;
  Vector rad(r.x,r.y,r.z);
  radius=rad.mag();
  radiusvar=radius;
  // center=r;
};


std::vector<point> Vertex;
std::vector<Vector> Norms;


Verts::Verts(std::vector<point>init){
  for(int i=0; i<init.size(); i++){
    Vertex.push_back(init[i]);
  }
}

Face::Face(std::vector<point> init){

        // GLint x=init[0];
        // GLint y=init[1];
        // GLint z=init[2];
        point p=init[0];
        point q=init[1];
        point r=init[2];
        // this grabs the point from the master vertex list

        // std::cout << "P:";
        // p.print();
        // std::cout << "Q:";
        // q.print();
        // std::cout << "R:";
        // r.print();

        Vector pq(p.x-q.x,p.y-q.y,p.z-q.z);
        // std::cout << "PQ: ";
        pq.normalize();
        // pq.print();

        Vector rq(r.x-q.x,r.y-q.y,r.z-q.z);
        // std::cout <<"RQ: ";
        rq.normalize();
        // rq.print();

        Vector norm(rq.cross(pq).getx(), rq.cross(pq).gety(), rq.cross(pq).getz());
        norm.normalize();
        // std::cout << "NORMAL VECTOR: ";
        // norm.print();
        // std::cout << std::endl;

    for(int i=0; i<init.size(); i++){
      // GLint j=init[i];
      // point a=Vertex[j];
      point x;
      // point x.set()
      FaceVerts.push_back(init[i]);
      FaceNorms.push_back(norm);
    }
    // norm.print();
  }


void  Mesh::draw(){
  for(int i=0; i<faces.size(); i++){
    glBegin(GL_POLYGON);
    for(int j=0; j<faces[i].FaceVerts.size(); j++){
      glNormal3d(faces[i].FaceNorms[j].getx(), faces[i].FaceNorms[j].gety(), faces[i].FaceNorms[j].getz());
      // glNormal3d(Norms[i].getx(), Norms[i].gety(), Norms[i].getz());
      glVertex3d(faces[i].FaceVerts[j].x, faces[i].FaceVerts[j].y, faces[i].FaceVerts[j].z);

    }
    glEnd();
    // std::cout << "VERT" << std::endl;
    // faces[i].FaceVerts[0].print();
    // std::cout << "NORMAL" << std:: endl;
    // faces[i].FaceNorms[0].print();
  }
}
Mesh::Mesh(std::vector<Face> init){
  for(int i=0; i<init.size(); i++){
    faces.push_back(init[i]);
  }
}
Mesh::Mesh(){

}
void Mesh::init(std::string fname){
  std::fstream fin;
  fin.open(fname, std::ios::in);
  if(fin.fail()){
    std::cout << fname << " failed to open." << std::endl;
    exit(0);
  }
  GLdouble numofvert, x, y, z;
  std::vector<point> temp1;
  fin >> numofvert;
  // std::cout << "NUMBER OF VERTICIES " << numofvert << std::endl;
  for(int i=0; i<numofvert; i++){
    fin >> x >> y >> z;
    point p;
    p.set(x,y,z);
    // p.print();
    temp1.push_back(p);
  }
  Verts verticies(temp1);
  GLint numofFaces, FaceVerts, vert;
  // for(int i=0; i<numofNorms; i++){
  //   GLdouble x, y, z;
  //   fin >> x >> y >> z;
  //   Vector norm(x,y,z);
  //   Norms.push_back(norm);
  // }
  fin >> numofFaces;
  // std::cout << "NUMBER OF FACES " << numofFaces << std::endl;
  // std::cout << std::endl;

  for(int i=0; i<numofFaces; i++){
    fin >> FaceVerts;
    // std::cout << FaceVerts << " | ";
    std::vector<GLint> temp2;
    for(int j=0; j<FaceVerts; j++){
      fin >> vert;
      // std::cout << vert << ", ";
      temp2.push_back(vert);
    }

    // std::cout << std::endl;
    // std::cout << "NORMAL VECTOR:" << std::endl;
    // Norms[i].print();
    // std::cout << std::endl;
    // Face ftemp(temp2);
    // faces.push_back(ftemp);
  }
  fin.close();
}
