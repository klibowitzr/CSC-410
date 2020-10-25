#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

GLint WIDTH=640, HEIGHT=480, VERT=0, MOVING=0;
point alphas, alpha2s, alpha3s,A, B, C, temp;
std::vector<point> inscribed, Points;
GLdouble radius1, radius2, radius3;
Vector a, b, c;

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
    exit(0);
    break;
  }
}

void setglobals(){
  if(Points.size()>0){
    A=Points[0];
    B=Points[1];
    C=Points[2];

    temp=B-A;
    Vector atemp(temp.x,temp.y,temp.z);
    a=atemp;
    temp=C-B;
    Vector btemp(temp.x,temp.y,temp.z);
    b=btemp;
    temp=A-C;
    Vector ctemp(temp.x,temp.y,temp.z);
    c=ctemp;
  }
}

void setmidpoints(point& acmid, point& bcmid, point& bamid, point A, point B, point C){
  acmid.x=(A.x+C.x)/2;
  acmid.y=(A.y+C.y)/2;
  bcmid.x=(C.x+B.x)/2;
  bcmid.y=(C.y+B.y)/2;
  bamid.x=(A.x+B.x)/2;
  bamid.y=(A.y+B.y)/2;
}

void nineptcircle(){
  if(Points.size()>0){
    point acmid, bcmid, bamid,S, temp, r, AA, BB, CC;
    GLdouble  mult, radius;
    Vector aaperp,d,e,f, aa, bb, cc;
    setmidpoints(acmid,bcmid,bamid,A,B,C);
    AA=bamid;
    BB=bcmid;
    CC=acmid;
    temp=BB-AA;
    Vector aatemp(temp.x,temp.y,temp.z);
    aa=aatemp;
    temp=CC-BB;
    Vector bbtemp(temp.x,temp.y,temp.z);
    bb=bbtemp;
    temp=AA-CC;
    Vector cctemp(temp.x,temp.y,temp.z);
    cc=cctemp;
    circl3(radius3, alpha3s, aa,bb,cc,AA);
  }
}

void inscribedcircle(){
  if(Points.size()>0){
    point qumid, tumid, qtmid,S, temp, r, U, Q, T;
    GLdouble  mult, radius, la, lb;
    Vector qperp,d,e,f, tempv;

    la=(a.mag()+c.mag()-b.mag())/2;
    lb=(a.mag()+b.mag()-c.mag())/2;
    a.normalize();
    tempv=a.mult(la);
    U=tempv.add(A);
    b.normalize();
    tempv=b.mult(lb);
    Q=tempv.add(B);
    c.normalize();
    tempv=c.mult(-1*la);
    T=tempv.add(A);

    setmidpoints(qumid,tumid,qtmid,Q,T,U);
    temp=T-Q;
    Vector aa(temp.x, temp.y, temp.z);
    temp=U-T;
    Vector bb(temp.x, temp.y, temp.z);
    temp=Q-U;
    Vector cc(temp.x, temp.y, temp.z);
    circl3(radius2, alpha2s,aa,bb,cc,Q);
  }
}


void excircle(){
  if(Points.size()>0){
    circl3(radius1,alphas,a,b,c,A);
  }
}

void myDisplay(){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glBegin(GL_LINE_LOOP);
  glColor3f(0.0,0.0,0.0);
  for(GLint i=0; i<Points.size(); i++){
    glVertex2d(Points[i].x, Points[i].y);
  }
  glEnd();
  glColor3f(1.0,0.0, 0.0);
  circle(radius1,alphas.x,alphas.y,0);
  glColor3f(0.0,1.0,0.0);
  circle(radius2,alpha2s.x, alpha2s.y,0);
  glColor3f(0.0,0.0,1.0);
  circle(radius3,alpha3s.x, alpha3s.y,0);
  glFlush();
}

  void myMouse(int button, int state, int x, int y){
    point p;
    GLdouble xrange, yrange;
    if(button==GLUT_LEFT_BUTTON && VERT!=3){
      if(state==GLUT_UP){
        p.x=x;
        p.y=HEIGHT-y;
        Points.push_back(p);
        VERT++;
      }
    }
    if(VERT==3){
      MOVING=1;
      setglobals();
      nineptcircle();
      excircle();
      inscribedcircle();
      glutPostRedisplay();
    }
  }

  int main(int argc, char* argv[]){
    std::cout << "e:exit"<< std::endl;
    std::cout << "Click in three noncollinear spots to create a triangle." << std::endl;
      glutInit(&argc, argv);
    	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    	glutInitWindowSize(WIDTH,HEIGHT);
    	glutInitWindowPosition(100, 150);
    	glutCreateWindow("Circles");
      glClear(GL_COLOR_BUFFER_BIT);
      glutMouseFunc(myMouse);
      glutDisplayFunc(myDisplay);
      glutKeyboardFunc(myKeyboardFunc);
    	myInit();
    	glutMainLoop();
    }
