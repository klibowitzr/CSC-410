#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
// std::fstream fn;
std::string fname;
GLint WIDTH=640, HEIGHT=480;
void myInit(void){
  GLdouble x, y;
   glClearColor(0.00, 0.0, 0.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   glPointSize(4.0);
   // setWorldWin(0.0,WIDTH,0.0,HEIGHT);
}

void myDisplay(){
  // polyline test("test.dat");

polydrawing dino(fname);
  // dino.getsize();
  dino.draw();
}

void myKeyboardFunc(unsigned char key, int mousex, int mousey){
  switch(key){
    case 'e':
    exit(0);
  }
}

int main(int argc, char* argv[]){
  fname=argv[1];
    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WIDTH,HEIGHT);
    // glutInitWindowSize(dino.getxmax()-dino.getxmin(), dino.getymax()-dino.getymin());
  	glutInitWindowPosition(100, 150);
  	glutCreateWindow("Dino");
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboardFunc);
  	myInit();
  	glutMainLoop();
  }
