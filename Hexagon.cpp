#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"
#include <cstdlib>
#include <iostream>

GLint WIDTH=640, HEIGHT=480;
GLint radius, sides;

void myInit(void){
  GLdouble x, y;
   glClearColor(0.00, 0.0, 0.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   glPointSize(4.0);
   setWorldWin(0.0,WIDTH,0.0,HEIGHT);
}

void myDisplay(){
  // drawngon(6,100, WIDTH/2, HEIGHT/2);
  drawngonswirl(sides,radius,WIDTH/2,HEIGHT/2);
  // std::cout << "calling from myDisplay" << std::endl;
}

void myKeyboardFunc(unsigned char key, int mousex, int mousey){
  switch(key){
    case 'e':
    exit(0);
    break;
  }
}

int main(int argc, char* argv[]){
  std::cout << "Enter number of sides:" << std::endl;
  std::cin>>sides;
  std::cout << "Enter radius: (150-200 works best!)" << std::endl;
  std::cin>>radius;
  std::cout << "e:exit"<< std::endl;
    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WIDTH,HEIGHT);
  	glutInitWindowPosition(100, 150);
  	glutCreateWindow("Polygon Swirl");
    glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboardFunc);
  	myInit();
  	glutMainLoop();
  }
