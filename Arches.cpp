#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

GLint WIDTH=640, HEIGHT=480;
GLint selection=1;

void myInit(void){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(4.0);
  glLineWidth(2.0);
  setWorldWin(0.0,WIDTH,0.0,HEIGHT);
}
void myDisplay(){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  if(selection==1){
    roundarch(200,200,WIDTH,HEIGHT);
  }
  else if(selection==2){
    pointedarch(200,200,WIDTH,HEIGHT);
  }
  else if(selection==3){
    ogeearch(200,200,WIDTH,HEIGHT);
    //I messed around with these values and they all seemed to work
    //nicely or near nicely ( a few pixels off sometimes?)
  }
}

void myKeyboardFunc(unsigned char key, int mousex, int mousey){
  switch(key){
    case 'e':
    exit(0);
    break;
    case '1':
    selection=1;
    glutPostRedisplay();
    break;
    case '2':
    selection=2;
    glutPostRedisplay();
    break;
    case '3':
    selection=3;
    glutPostRedisplay();
    break;
  }
}



int main(int argc, char* argv[]){
  std::cout << "e:exit"<< std::endl;
    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WIDTH,HEIGHT);
  	glutInitWindowPosition(100, 150);
  	glutCreateWindow("Arches");
    glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboardFunc);
  	myInit();
  	glutMainLoop();
  }
