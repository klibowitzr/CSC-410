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
void snowflake(){
  glBegin(GL_LINE_STRIP);
  glVertex2d(15,10);
  glVertex2d(100,10);
  glVertex2d(150,50);
  glVertex2d(200,50);
  glVertex2d(150,10);
  glVertex2d(300,10);
  glVertex2d(325,0);
  glEnd();
}
void myDisplay(){
  glMatrixMode(GL_MODELVIEW);
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glTranslated(WIDTH/2,HEIGHT/2,0);

  glScaled(0.5,0.5,1);
  for(GLint i=0; i<6; i++){
    snowflake();
    glScaled(1,-1,1);
    snowflake();
    glScaled(1,-1,1);
    glRotated(60,0,0,1);
  }
  glFlush();
}


int main(int argc, char* argv[]){

  std::cout << "e:exit"<< std::endl;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Snowflake");
  glClear(GL_COLOR_BUFFER_BIT);
  myInit();
  glutDisplayFunc(myDisplay);
  // glutIdleFunc(idle);
  glutKeyboardFunc(myKeyboardFunc);
  glutMainLoop();

  }
