#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"
#include <cstdlib>
#include <iostream>


GLint WIDTH=640, HEIGHT=480;
GLint radius;
void myInit(void){
  // glClearColor(1.0, 1.0, 1.0, 0.0);
  // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  // glColor3f(0.0, 0.0, 0.0);
  glPointSize(4.0);
  setWorldWin(0.0,WIDTH,0.0,HEIGHT);
}


void myKeyboardFunc(unsigned char key, int mousex, int mousey){
  switch(key){
    case 'e':
    exit(0);
    break;
  }
}

void myDisplay(){
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  yinyang(radius, WIDTH/2, HEIGHT/2);
  // halfcirc(200, 0, WIDTH/2, HEIGHT/2, 0);
}

int main(int argc, char* argv[]){
  std::cout <<  "Radius:" << std::endl;
  std::cin >> radius;
    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WIDTH,HEIGHT);
  	glutInitWindowPosition(100, 150);
  	glutCreateWindow("YinYang");
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboardFunc);
  	myInit();
  	glutMainLoop();
  }
