#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"
#include <cstdlib>
#include <iostream>


GLint WIDTH=640, HEIGHT=480;
GLint selection=0, k, petals;
void myInit(void){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glColor3f(0.0, 0.0, 0.0);
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
  if(selection==1){
    cardioid(k, WIDTH/2, HEIGHT/2);
  }
  if(selection==2){
    rosecurve(k,petals,WIDTH/2, HEIGHT/2);
  }
  if(selection==3){
    archcurve(k,WIDTH/2,HEIGHT/2);
  }
}

int main(int argc, char* argv[]){
  std::cout << "Make a selection:" << std::endl;
  std::cout << "Select 1 for Cardioid" << std::endl;
  std::cout << "Select 2 for Rose" << std::endl;
  std::cout << "Select 3 for Archimedean Spiral" << std::endl;
  std::cin >> selection;
  while(selection!=1 && selection!=2 && selection!=3){
        std::cout << "Please make a valid selection." << std::endl;
        std::cin >> selection;
  }
  if(selection==2){
    std::cout << "Enter a constant: " << std::endl;
    std::cin >> k;
    std::cout << "Enter number of petals: " << std::endl;
    std::cin >> petals;
  }
  else if(selection==1 || selection==3){
    std::cout << "Enter a constant:" << std::endl;
    std::cin>>k;
  }



    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WIDTH,HEIGHT);
  	glutInitWindowPosition(100, 150);
  	glutCreateWindow("Graphs");
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboardFunc);
  	myInit();
  	glutMainLoop();
  }
