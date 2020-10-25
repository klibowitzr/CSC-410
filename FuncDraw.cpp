#include "globalgl.h"
#include "Utils.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <math.h>
const GLint HEIGHT=480, WIDTH=640;
const GLint HSCALE1=HEIGHT/2-20;
const GLint HBUFFER1=HEIGHT/2;
const GLint WSCALE1=WIDTH/(2*M_PI)-5;
const GLint WBUFFER1=20;


const GLint HSCALE2=HEIGHT/2-20;
const GLint HBUFFER2=HEIGHT/2;
const GLint WSCALE2=WIDTH/4-65;
const GLint WBUFFER2=20;

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
 void myInit(void)
 {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(4.0);
    setWorldWin(0.0,640,0.0,480);
}
GLdouble f(GLdouble(x)) {
    return sin(x);
}
GLdouble g(GLdouble(x)){
  return exp(-fabs(x))*cos(2*M_PI*x);
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>

void myDisplay1(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINE_STRIP);

for (GLdouble x = 0.0; x < 2*M_PI; x+=0.05) {
    glVertex2d( WSCALE1*x+WBUFFER1, HSCALE1*f(x)+HBUFFER1);
  }
    glEnd();
    glFlush();
}

void myDisplay2(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINE_STRIP);

for (GLdouble x = 0.0; x < 2*M_PI; x+=0.005) {
    glVertex2d( WSCALE2*x+WBUFFER2, HSCALE2*g(x)+HBUFFER2);
  }
    glEnd();
    glFlush();
}
void (*myDisplay)(void);
void myKeyboard(unsigned char key, int mousex, int mousey){
  switch(key){
    case '1':
      myDisplay=myDisplay1;
      glutDisplayFunc(myDisplay1);
      break;
    case '2':
    myDisplay=myDisplay2;
    glutDisplayFunc(myDisplay2);
    break;
    case 'e':
      exit(0);
    default:
      myDisplay=myDisplay1;
      glutDisplayFunc(myDisplay1);
      break;
  }
  glutPostRedisplay();
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char* argv[])
{
    void (*displaythis)(void);
    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(640,480);
  	glutInitWindowPosition(100, 150);
  	glutCreateWindow("Function Drawer");
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(myDisplay1);
    glutKeyboardFunc(myKeyboard);

  	myInit();
  	glutMainLoop();
}
