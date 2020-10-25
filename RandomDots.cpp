#include "globalgl.h"
#include "Utils.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>

std::vector<int> xcoords, ycoords;
std::vector<int>::iterator itx, ity;
const GLint WINSIZE=500;
const GLint A=1103515245;
const GLint B=12345;
const GLint N=32767;

void myInit(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   glPointSize(4.0);
   setWorldWin(0.0,WINSIZE,0.0,WINSIZE);
}

void makepointsgut(){
  srand(time(NULL));
  GLint point;
  for(int i=0; i<500; i++){
    point=rand()%500;
    xcoords.push_back(point);
  }
  for(int j=0; j<500; j++){
    point=rand()%500;
    ycoords.push_back(point);
  }
}

void makepointschlecht(){
  srand(time(NULL));
  GLint point=rand();
  for(int i=0; i<500; i++){
    point=(point*A+B)%N;
    xcoords.push_back(point%500);
  }
   point=rand();
  for (int j=0; j<500; j++){
    point=(point*A+B)%N;
    ycoords.push_back(point%500);
  }
}

void myDisplay(void){
  glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for(itx=xcoords.begin(), ity=ycoords.begin(); itx!=xcoords.end()
     && ity!=ycoords.end(); ++ity, ++itx){
      glVertex2i(*itx,*ity);
    }
  glEnd();
  glFlush();
}
void myKeyboard(unsigned char key, int mousex, int mousey){
  switch(key){
    case '1':
    xcoords.clear();
    ycoords.clear();
    makepointsgut();
    glutPostRedisplay();
    break;
    case '2':
    xcoords.clear();
    ycoords.clear();
    makepointschlecht();
    glutPostRedisplay();
    break;
    case 'e':
    exit(0);
  }
}
int main(int argc, char* argv[])
{
    std::cout << "1:rand() function " << std::endl;
    std::cout << "2: Function from book " << std::endl;
    std::cout << "e: Exit" << std::endl;
    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WINSIZE,WINSIZE);
  	glutInitWindowPosition(100, 150);
  	glutCreateWindow("Random Dot Plotter");
    glClear(GL_COLOR_BUFFER_BIT);
    makepointsgut(); //default function
    glutKeyboardFunc(myKeyboard);
    glutDisplayFunc(myDisplay);
  	myInit();
  	glutMainLoop();
}
