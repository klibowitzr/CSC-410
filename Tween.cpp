#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

GLint WIDTH=640, HEIGHT=480, VERT=0;
point alphas, alpha2s, alpha3s,A, B, C, temp;
std::vector<point> inscribed, Points, tween;
GLdouble radius1, radius2, radius3;
Vector a, b, c;
GLdouble t=0;
// polyline squarepoly("square.dat");
// polyline circlepoly("circle.dat");

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

void Tween(polyline A, polyline B, GLint n, GLdouble t){
  if(tween.size()>0){
    tween.clear();
  }
  for(GLint i=0; i<n; i++){
    point p;
      p.x=A.ppoints[i].x + ((B.ppoints[i].x-A.ppoints[i].x)*t);
      p.y=A.ppoints[i].y + ((B.ppoints[i].y-A.ppoints[i].y)*t);
      tween.push_back(p);
  }
}

void idle(){
  t+=0.1;
  delay(100);
  glutPostRedisplay();
}

void myDisplay(){

  if(t<=1){
    polyline squarepoly("square.dat");
    polyline circlepoly("circle.dat");
    //I know this is horrible but for some reason I keep getting
    //segmentation fault:11 when I declare these as globals? I figured
    //it was at least better to put it inside the loop so the file is read
    //only ten times rather than every time myDisplay is called

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    Tween(squarepoly,circlepoly, squarepoly.ppoints.size(),t);
    // std::cout << "t from mydisplay " << t << std::endl;
    if(tween.size()>0){
      glBegin(GL_LINE_STRIP);
      for(GLint i=0; i<tween.size(); i++){
        glVertex2d(tween[i].x, tween[i].y);
      }
      glEnd();
    }
    glFlush();
    glutSwapBuffers();
  }
}


int main(int argc, char* argv[]){
  std::cout << "e:exit"<< std::endl;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Tween");
  glClear(GL_COLOR_BUFFER_BIT);
  myInit();
  glutDisplayFunc(myDisplay);
  glutIdleFunc(idle);
  glutKeyboardFunc(myKeyboardFunc);
  glutMainLoop();

  }
