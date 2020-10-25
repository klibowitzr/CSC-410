#include "globalgl.h"
#include "Utils.h"
#include <math.h>
#include <iostream>
const GLint WIDTH=600;
const GLint HEIGHT=400;
const GLdouble LFEE =(1+sqrt(5))/2;
const GLdouble SFEE=1/LFEE;




void myInit(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   glPointSize(8.0);
   setWorldWin(0.0,WIDTH,0.0,HEIGHT);
 }
void rect1(double x1, double y1, double width, double height){
  width=width/LFEE;
  height=height*SFEE;
  glBegin(GL_LINE_LOOP);
    glVertex2d(x1,y1);
    glVertex2d(x1+width,y1);
    glVertex2d(x1+width,y1+height);
    glVertex2d(x1,y1+height);
  glEnd();
  glFlush();
  glBegin(GL_LINE_STRIP);
    glVertex2d(x1,y1+height);
    glVertex2d(x1+width,y1);
  glEnd();
  glFlush();
}
void rect2(double x1, double y1, double width, double height){
  width=width/LFEE;
  height=height;
  glBegin(GL_LINE_LOOP);
    glVertex2d(x1,y1);

    glVertex2d(width,y1);
    glVertex2d(width,height);
    glVertex2d(x1,height);
  glEnd();
  glFlush();
  glBegin(GL_LINE_STRIP);
    glVertex2d(x1,height);
    glVertex2d(width,y1);
  glEnd();
  glFlush();
}

void rect3(double x1, double y1, double width, double height){
  width=width;
  height=height-(height/LFEE);
  glBegin(GL_LINE_LOOP);
    glVertex2d(x1,y1+height);
    glVertex2d(width,y1+height);
    glVertex2d(width,y1);
    glVertex2d(x1,y1);
  glEnd();
  glFlush();
  glBegin(GL_LINE_STRIP);
    glVertex2d(x1,y1);
    glVertex2d(width,y1+height);
  glEnd();
  glFlush();
}

void rect4(double x1, double y1, double width, double height){
height=height-(height/LFEE);
std::cout << width << std::endl;
width=width+(height/LFEE);
// std::cout << width << " " << height << std::endl;
// std::cout << x1 << " " << y1 << std::endl;
glBegin(GL_LINE_LOOP);
  glVertex2d(x1,height);
  glVertex2d(width,height);
  glVertex2d(width,y1);
  glVertex2d(x1,y1);
glEnd();
glFlush();
}

void myDisplay(){
  GLdouble curxpos1=0, curxpos2, curypos1=0, curypos2;
  GLdouble curheight=HEIGHT;
  GLdouble curwidth=WIDTH;
  // while(curheight>1 && curwidth>1){
    rect1(curxpos1,curypos1, curwidth, curheight);
    curwidth=curwidth/LFEE;
    curheight=curheight*SFEE;
    curxpos1=curwidth;
    rect2(curxpos1,curypos1,curwidth,curheight);
    curwidth=curwidth/LFEE;
    rect3(curxpos1,curypos1,curwidth,curheight);
    curxpos1=curwidth;
    // curypos1=curheight-(curheight/LFEE);
    rect4(curxpos1,curypos1,curwidth,curheight);
// }
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
