#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"
#include <cmath>

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

GLint WIDTH=640, HEIGHT=480, DRAW=1;
std::string fname;
polydrawing dino;
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
    break;
    case '2':
    DRAW=2;
    break;
  }
  glutPostRedisplay();
}
void draw1(){
// setWorldWin(dino.getxmin(), dino.getxmax(), dino.getymin(),dino.getymax());
  //I can declare global polylines but not polydrawings, I'm
  //working on figuring this out
  glMatrixMode(GL_MODELVIEW);
  GLdouble x, y, theta;
  theta=0.0;
  for(GLint i=0; i<12; i++){
    x=((125*cos(degtorad(theta)))+WIDTH/2);
    y=((125*sin(degtorad(theta)))+HEIGHT/2);
    glPushMatrix();
    glTranslated(x,y,1);
    glScaled(0.1,0.1,0.1);
    theta+=(360.0/12);
    dino.draw();
    glPopMatrix();
  }
  DRAW=0;
  //I "unset" draw so that myDisplay doesn't keep Calling
  //draw1 (to prevent constant opening and reading of file)
}


void draw2(){
  // polydrawing dino(fname);
  // setWorldWin(dino.getxmin(), dino.getxmax(), dino.getymin(),dino.getymax());

  glMatrixMode(GL_MODELVIEW);

  GLdouble x, y, theta;
  theta=0.0;
  for(GLint i=0; i<12; i++){
    x=((125*cos(degtorad(theta)))+WIDTH/2);
    y=((125*sin(degtorad(theta)))+HEIGHT/2);
    glPushMatrix();
    glTranslated(x,y,1);
    glScaled(0.1,0.1,0.1);
    theta+=(360.0/12);
    glRotated((360/12)*i+270, 0, 0, 1);
    dino.draw();
    glPopMatrix();
  }
  DRAW=0;
  //same goes for here
}


void myDisplay(){
  // setWorldWin(dino.getxmin(), dino.getxmax(), dino.getymin(),dino.getymax());
  dino.world();
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  if(DRAW==1){
    draw1();
  }
  if(DRAW==2){
    draw2();
  }
  glFlush();
}

int main(int argc, char* argv[]){
  if(!argv[1]){
    std::cout << "Please provide filename." << std::endl;
    std::cin>>fname;
  }
  else{
    fname=argv[1];
  }
  dino.init(fname);
  // dino.world();
  std::cout << "e:exit"<< std::endl;
  std::cout << "Press 1 and 2 to toggle" << std::endl;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Dinoclocks");
  glClear(GL_COLOR_BUFFER_BIT);
  myInit();
  glutDisplayFunc(myDisplay);
  glutKeyboardFunc(myKeyboardFunc);
  glutMainLoop();

  }
