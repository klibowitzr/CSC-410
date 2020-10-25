#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
GLint WIDTH=640, HEIGHT=480;

void myInit(void){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(4.0);
  glLineWidth(2.0);
  setWorldWin(0.0,WIDTH,0.0,HEIGHT);
}

void myDisplay(){
  drawngon(82,100,WIDTH/2,HEIGHT/2);

}
int main(int argc, char* argv[]){
  // Vector a(2,1,-1);
  // Vector b(-3,4,1);
  // Vector d(3,4,0);
  // Vector e(1,1,1);
  // Vector c;
  // GLint x;
  // c=a.cross(b);
  // std::cout << "CROSS PRODUCT" << std::endl;
  // c.print();
  //
  // x=a.dot(b);
  // std::cout << "DOT PRODUCT" << std::endl;
  // std::cout << x << std::endl;
  //
  // c=a.add(b);
  // std::cout << "SUM" << std::endl;
  // c.print();
  //
  // c=a.sub(b);
  // std::cout << "DIFFERENCE" << std::endl;
  // c.print();
  //
  // x=d.mag();
  // std::cout << "MAGNITUDE" <<std::endl;
  // std::cout << x << std::endl;
  // e.normalize();
  // std::cout << "NORMALIZE" << std::endl;
  // e.print();
  // std::cout <<"A PERP" << std::endl;
  // c=a.perp();
  // c.print();
  // x=c.dot(a);
  // std::cout <<"Should be zero" << std::endl;
  // std::cout << x << std::endl;
  // c=a.mult(2);
  // std::cout << "Vector a multiplied by 2" << std::endl;
  // c.print();
  //


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Arches");
  glClear(GL_COLOR_BUFFER_BIT);

  glutDisplayFunc(myDisplay);
  // glutKeyboardFunc(myKeyboardFunc);
  myInit();
  glutMainLoop();
}
