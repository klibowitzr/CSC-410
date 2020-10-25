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
GLint orientation=-1;
GLdouble rows=1, cols=1;
GLdouble xmin,ymin, xmax,ymax;

std::string fname;
void myInit(void){
  GLdouble x, y;
   glClearColor(0.00, 0.0, 0.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   glPointSize(4.0);
}

void myDisplay(){
  polydrawing dino(fname);
  xmin=dino.getxmin();
  ymin=dino.getymin();
  xmax=dino.getxmax();
  ymax=dino.getymax();

  if(orientation==-1){
    dino.draw();
  }
  if(orientation==1){
    glClearColor(0.00, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setWorldWin(xmin,xmax,ymin,ymax);
    for(int i=0; i<cols; i++){
      for(int j=0; j<rows; j++){
        glViewport(i*(WIDTH/cols), j*(HEIGHT/rows), WIDTH/cols, HEIGHT/rows);
        dino.draw();
      }
    }
  }
  if(orientation==2){
    glClearColor(0.00, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setWorldWin(xmin,xmax,ymin,ymax);
    for(int i=0; i<cols; i++){
      for(int j=0; j<rows; j++){
        if((i+j)%2==0){
          setWorldWin(xmin,xmax,ymin,ymax);
        }
        else{
          setWorldWin(xmin,xmax,ymax,ymin);
        }
        glViewport(i*(WIDTH/cols), j*(HEIGHT/rows), WIDTH/cols, HEIGHT/rows);
        dino.draw();
      }
    }
  }
  if(orientation==3){
    glClearColor(0.00, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setWorldWin(xmin,xmax,ymin,ymax);
    for(int i=0; i<cols; i++){
      for(int j=0; j<rows; j++){
        if(i%2==0){
          setWorldWin(xmax,xmin,ymin,ymax);
        }
        else{
          setWorldWin(xmin,xmax,ymin,ymax);
        }
        glViewport(i*(WIDTH/cols), j*(HEIGHT/rows), WIDTH/cols, HEIGHT/rows);
        dino.draw();
      }
    }
  }
}

void myKeyboardFunc(unsigned char key, int mousex, int mousey){
  switch(key){
    case 'e':
    exit(0);
    break;
    case '1':
    orientation=1;
    glutPostRedisplay();
    break;
    case '2':
    orientation=2;
    glutPostRedisplay();
    break;
    case '3':
    orientation=3;
    glutPostRedisplay();
    break;
    case ' ':
    rows+=1;
    cols+=1;
    if(orientation==-1) orientation=1;
    orientation=orientation;
    glutPostRedisplay();
    break;
    case '\t':
    rows-=1;
    cols-=1;
    orientation=orientation;
    glutPostRedisplay();
    break;
  }
}

int main(int argc, char* argv[]){
  if(!argv[1]){
    std::cout << "Please provide filename." << std::endl;
    std::cin>>fname;
  }
  else{
    fname=argv[1];
  }
  std::cout << "Press spacebar to add row and column." <<std::endl;
  std::cout << "Press tab to remove row and column." << std::endl;
  std::cout << "Try pressing 1, 2, and 3 for different configurations." << std::endl;
  std::cout << "Press e to exit." << std::endl;
    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WIDTH,HEIGHT);
  	glutInitWindowPosition(100, 150);
  	glutCreateWindow("Dino");
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboardFunc);
  	myInit();
  	glutMainLoop();
  }
