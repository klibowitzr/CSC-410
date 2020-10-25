#include "globalgl.h"
#include "Utils.h"
#include <math.h>
#include <iostream>
const GLint WIDTH=600;
const GLint HEIGHT=400;
const GLdouble LFEE =(1+sqrt(5))/2;
const GLdouble SFEE=1/LFEE;

GLdouble curheight=HEIGHT;
GLdouble curwidth=WIDTH;
GLdouble curxpos1=0, curxpos2, curypos1=0, curypos2;
// curxpos1=0;
// curypos2=0;

void myInit(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   glPointSize(4.0);
   setWorldWin(0.0,WIDTH,0.0,HEIGHT);
 }

// void rect1(){
//   curxpos2=curwidth/LFEE;
//   curypos2=curheight*SFEE;
//   // glBegin(GL_LINE_LOOP);
//   //   glVertex2d(curxpos1,curypos1),
//   //   glVertex2d(curxpos1+curxpos2,curypos1),
//   //   glVertex2d(curxpos1+curxpos2,curypos1+curypos2);
//   //   glVertex2d(curxpos1,curypos1+curypos2);
//   //   glEnd();
//   //   std::cout << curxpos1 << " " << curypos1 << " " << curxpos2 << " "<< curypos2 << std::endl;
//   // glBegin(GL_LINE_STRIP);
//   // glVertex2d(curxpos1,curypos1+curypos2);
//   // glVertex2d(curxpos1+curxpos2,curypos1);
//   // glEnd();
//   // glFlush();
//   curheight=curypos2;
//   curwidth=curxpos2;
// }
//
// void rect2(){
//   curxpos2=curwidth/LFEE;
//   curypos2=curheight*SFEE;
//   glBegin(GL_LINE_LOOP);
//     glVertex2d(curxpos1,curypos1),
//     glVertex2d(curxpos1+curxpos2,curypos1),
//     glVertex2d(curxpos1+curxpos2,curypos1+curypos2);
//     glVertex2d(curxpos1,curypos1+curypos2);
//     glEnd();
//   std::cout << curxpos1 << " " << curypos1 << " " << curxpos2 << " "<< curypos2 << std::endl;
//   curheight=curypos2;
//   curwidth=curxpos2;
//   glEnd();
//   glFlush();
//   }
void rect3(){

}
void rect4(){

}
void myDisplay(){
  // while(curheight>1 && curwidth>1){
  curxpos2=curwidth/LFEE;
  curypos2=curheight*SFEE;
  glBegin(GL_LINE_LOOP);
    glVertex2d(curxpos1,curypos1),
    glVertex2d(curxpos1+curxpos2,curypos1),
    glVertex2d(curxpos1+curxpos2,curypos1+curypos2);
    glVertex2d(curxpos1,curypos1+curypos2);
    glEnd();
    std::cout << curxpos1 << " " << curypos1 << " " << curxpos2 << " "<< curypos2 << std::endl;
  glBegin(GL_LINE_STRIP);
  glVertex2d(curxpos1,curypos1+curypos2);
  glVertex2d(curxpos1+curxpos2,curypos1);
  glEnd();
  glFlush();
  curheight=curypos2;
  curwidth=curxpos2;
}

 int main(int argc, char* argv[])
 {
     glutInit(&argc, argv);
   	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   	glutInitWindowSize(WIDTH,HEIGHT);
   	glutInitWindowPosition(100, 150);
   	glutCreateWindow("Golden Rectangle");
     glClear(GL_COLOR_BUFFER_BIT);
     // glutKeyboardFunc(myKeyboard);
     glutDisplayFunc(myDisplay);
   	myInit();
   	glutMainLoop();
 }
