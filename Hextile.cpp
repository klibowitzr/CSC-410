#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

GLint WIDTH=640, HEIGHT=480;
GLint rows=4, cols=5, view=100;

void myInit(void){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(4.0);
  // setWorldWin(0.0,WIDTH,0.0,HEIGHT);
}

void myDisplay(){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  // setWorldWin(-50,50,-50,50);
  for(GLint i=0; i<cols; i++){
    for(GLint j=0; j<rows; j++){
      if((i+j)%2==0){
        setWorldWin(WIDTH/2+view, WIDTH/2-view, HEIGHT/2-view, HEIGHT/2+view);
      }
      else{
        setWorldWin(WIDTH/2-view, WIDTH/2+view, HEIGHT/2-view, HEIGHT/2+view);

      }
      GLint x=WIDTH/cols;
      GLint y=HEIGHT/rows;
      setViewPort(i*x, x+i*x, j*y, y+j*y);
      drawngonswirl(6,200,WIDTH/2, HEIGHT/2);
    }
  }


}
void myKeyboardFunc(unsigned char key, int mousex, int mousey){
  switch(key){
    case 'e':
    exit(0);
    break;
    case '+':
    rows++;
    cols++;
    glutPostRedisplay();
    break;
    case '-':
    rows--;
    cols--;
    if(rows<4) rows=4;
    if(cols<5) cols=5;
    glutPostRedisplay();
    break;
  }
}
int main(int argc, char* argv[]){
  std::cout << "+/-: add or subtract rows and columns" << std::endl;
  std::cout << "e:exit"<< std::endl;
    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WIDTH,HEIGHT);
  	glutInitWindowPosition(100, 150);
  	glutCreateWindow("Hexswirl Tile");
    glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboardFunc);
  	myInit();
  	glutMainLoop();
  }
