#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

GLint WIDTH=640, HEIGHT=480, DRAW=0;
GLdouble xview=0, yview=0, zview=3;
std::string fname;
std::vector<point>ppoints;
void makeprism(){
  point p,q,r,s,t;
  // point p;
  p.set(3,0,0);
  q.set(6,0,0);
  r.set(7,3,0);
  s.set(5,5,0);
  t.set(2,3,0);
  ppoints.push_back(p);
  ppoints.push_back(q);
  ppoints.push_back(r);
  ppoints.push_back(s);
  ppoints.push_back(t);
  std::vector<Face> faces;
  for(int i=0; i<ppoints.size()-1; i++){
    //vertical sides of prism
    std::vector<point> pface;
    point p, q, r, s;
    p.set(ppoints[i].x, ppoints[i].y,0);
    pface.push_back(p);
    q.set(ppoints[i+1].x, ppoints[i+1].y,0);
    pface.push_back(q);
    r.set(ppoints[i+1].x, ppoints[i+1].y,1);
    pface.push_back(r);
    s.set(ppoints[i].x, ppoints[i].y,1);
    pface.push_back(s);
    faces.push_back(pface);
  }
    //top and bottom of prism
    std::vector<point>  pface;
    for(int j=0; j<ppoints.size(); j++){
      point p;
      p.set(ppoints[j].x, ppoints[j].y,0);
      pface.push_back(p);
    }
    faces.push_back(pface);
    pface.clear();
    for(int j=0; j<ppoints.size(); j++){
      point p;
      p.set(ppoints[j].x, ppoints[j].y,1);
      pface.push_back(p);
    }
    faces.push_back(pface);
  Mesh myprism(faces);
  myprism.draw();
}

void myInit(void){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(4.0);
  glLineWidth(2.0);
  setWorldWin(0.0,WIDTH,0.0,HEIGHT);
}

void myKeyboardFunc(unsigned char key, int mousex, int mousey){
    switch(key){
    case 'e':
    std::cout << xview << " " << yview << " " << zview << std::endl;
    exit(0);
    break;
    case 'a':
    xview-=0.5;
    break;
    case 'd':
    xview+=0.5;
    break;
    case 's':
    yview-=0.5;
    break;
    case 'w':
    yview+=0.5;
    break;
    case 'z':
    zview-=0.5;
    break;
    case 'c':
    zview+=0.5;
    break;
  }
  glutPostRedisplay();
}

void myDisplay(){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  GLfloat mat_ambient[]={0.8f, 0.8f, 0.8f, 1.0f};
  GLfloat mat_diffuse[]={0.6f, 0.6f, 0.6f,1.0f};
  GLfloat mat_specular[]={0.5f,0.5f,0.5f,1.0f};

  GLfloat mat_shininess[]={50.0f};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  GLfloat lightIntensity[]={0.5f, 0.0f, 0.7f, 1.0f};
  GLfloat light_position[]={20.0,10.0,20,0.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
  GLfloat light_position2[]={-20.0,10.0,20,0.0f};

  glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10,10,-10,10,-10,50);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(xview,yview,zview,3,1,1,0,1,0);
  glPushMatrix();
  makeprism();
  glPopMatrix();
  glFlush();
}

int main(int argc, char* argv[]){
  std::cout << "a/d: change eye.x" << std::endl;
  std::cout << "w/s: change eye.y" << std::endl;
  std::cout << "z/c: change eye.z" << std::endl;
  std::cout << "e:exit"<< std::endl;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Prism");
  glClear(GL_COLOR_BUFFER_BIT);
  myInit();
  glutDisplayFunc(myDisplay);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glutKeyboardFunc(myKeyboardFunc);
  glutMainLoop();
  }
