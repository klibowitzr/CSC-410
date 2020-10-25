#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
// std::fstream fn;
GLdouble WIDTH=640,HEIGHT=480;
GLint sides=4;

std::string fname;
void myInit(void){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(4.0);
  setWorldWin(0.0,WIDTH,0.0,HEIGHT);
}

void myDisplay(){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  rosette(sides, 200, WIDTH/2, HEIGHT/2);
}

void myKeyboardFunc(unsigned char key, int mousex, int mousey){
  switch(key){
    default:
    glutPostRedisplay();
    break;
    case 'e':
    exit(0);
    break;
    case '+':
    sides++;
    glutPostRedisplay();
    break;
    case '-':
    sides--;
    if(sides<4) sides=4;
    glutPostRedisplay();
    break;
  }
}

int main(int argc, char* argv[]){
  std::cout << "Press + or - to change the number of sides." << std::endl;
  std::cout << "Press e to exit." << std::endl;
    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WIDTH,HEIGHT);
  	glutInitWindowPosition(100, 150);
  	glutCreateWindow("Rosette");
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboardFunc);
  	myInit();
  	glutMainLoop();
  }
