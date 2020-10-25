#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
polyline house("House.dat");

GLint WIDTH=640, HEIGHT=480, DRAW=0;
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
    case '1':
    DRAW=1;
    glutPostRedisplay();
    break;
    case '2':
    DRAW=2;
    glutPostRedisplay();
    break;
    case '3':
    DRAW=3;
    glutPostRedisplay();
    break;
    case '4':
    DRAW=4;
    glutPostRedisplay();
    break;
  }
}
void draw1(){
  glMatrixMode(GL_MODELVIEW);
  // glPushMatrix();
  glScaled(0.5,0.5,0);
  house.draw();
  // glPopMatrix();
}
void draw2(){
  glMatrixMode(GL_MODELVIEW);
  // glPushMatrix();
  glScaled(2,2,0);
  house.draw();
  // glPopMatrix();
}
void draw3(){
  glMatrixMode(GL_MODELVIEW);
  // glPushMatrix();
  glRotated(10,0,0,1);
  house.draw();
  // glPopMatrix();
}
void draw4(){
  glMatrixMode(GL_MODELVIEW);
  // glPushMatrix();
  glTranslated(100,50,0);
  house.draw();
  // glPopMatrix();
}
//I didn't push and pop because I wanted the transformations
//to be stackable 
void myDisplay(){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  if(DRAW==0){
    house.draw();
  }
  if(DRAW==1){
    draw1();
  }
  if(DRAW==2){
    draw2();
  }
  if(DRAW==3){
    draw3();
  }
  if(DRAW==4){
    draw4();
  }
}

int main(int argc, char* argv[]){
  std::cout << "1: shrink" << std::endl;
  std::cout << "2: Grow" << std::endl;
  std::cout << "3: Rotate 10 degrees" << std::endl;
  std::cout << "4: Translate" << std::endl;
  std::cout << "e:exit"<< std::endl;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Houses");
  glClear(GL_COLOR_BUFFER_BIT);
  myInit();
  glutDisplayFunc(myDisplay);
  // glutIdleFunc(idle);
  glutKeyboardFunc(myKeyboardFunc);
  glutMainLoop();

  }
