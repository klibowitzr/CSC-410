#include "globalgl.h"
#include "Utils.h"
#include <math.h>
#include <iostream>
const GLdouble  WIDTH=600;
const GLdouble HEIGHT=400;
const GLdouble FEE =(1+sqrt(5))/2;
const GLdouble SFEE=1/FEE;
// const GLdouble SFEE=1/LFEE;
GLdouble gx=0,gy=0,gheight=HEIGHT,gwidth=WIDTH;
GLint orientation=-1;
GLint firstround=1;

void myInit(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   glPointSize(8.0);
   setWorldWin(0.0,WIDTH,0.0,HEIGHT);
 }

 void bottomleft(GLdouble &x, GLdouble &y, GLdouble &width, GLdouble &height){
   if(firstround==1){
     //Gets the beginning position for the entire program
     width=(HEIGHT/WIDTH)*(HEIGHT*FEE);
     height=(HEIGHT/WIDTH)*HEIGHT;
     firstround=0;
   }
   else{
     GLdouble temp;
     x=x-width;
     y=height/FEE+y;
     temp=height/FEE;
     height=height-temp;
   }
   // std::cout << "BOTTOM LEFT RECTANGLE:"<< std::endl;
   // std::cout << "WIDTH: " << width << " " << "HEIGHT: " << height << std::endl;
   // std::cout << "X: " << x << " " << "Y: " << y << std::endl;
   // std::cout<<std::endl;
 }
 void topleft(GLdouble &x, GLdouble &y, GLdouble &width, GLdouble &height){
   GLdouble temp;
   temp=height;
   height=width-height;
   width=temp;
   y=y+width;
   x=x+width;
   // std::cout << "TOP LEFT RECTANGLE:"<< std::endl;
   // std::cout << "WIDTH: " << width << " " << "HEIGHT: " << height << std::endl;
   // std::cout << "X: " << x << " " << "Y: " << y << std::endl;
   // std::cout<<std::endl;
 }
 void topright(GLdouble &x, GLdouble &y, GLdouble &width, GLdouble &height){
   GLdouble temp;
   temp=width;
   x=x+height;
   y=y-height;
   width=height;
   height=width/FEE;
   // height=height-temp/FEE;
   // std::cout << "TOP RIGHT RECTANGLE:"<< std::endl;
   // std::cout << "WIDTH: " << width << " " << "HEIGHT: " << height << std::endl;
   // std::cout << "X: " << x << " " << "Y: " << y << std::endl;
   // std::cout<<std::endl;
 }
 void bottomright(GLdouble &x, GLdouble &y, GLdouble &width, GLdouble &height){
   y=y-height;
   x=x-width/FEE;
   width=width-width/FEE;
   // std::cout << "TOP RIGHT RECTANGLE:"<< std::endl;
   // std::cout << "WIDTH: " << width << " " << "HEIGHT: " << height << std::endl;
   // std::cout << "X: " << x << " " << "Y: " << y << std::endl;
   // std::cout<<std::endl;
 }

void myDisplay(){
  if(orientation==0){
    glBegin(GL_LINE_LOOP);
      glVertex2d(gx,gy);
      glVertex2d(gx+gwidth,gy);
      glVertex2d(gx+gwidth,gy+gheight);
      glVertex2d(gx,gy+gheight);
    glEnd();
    glFlush();
    glBegin(GL_LINE_STRIP);
      glVertex2d(gx,gy+gheight);
      glVertex2d(gx+gwidth,gy);
    glEnd();
    glFlush();
    // glBegin(GL_POINTS);
    //   glVertex2d(gx,gy);
    // glEnd();
    // glFlush();
  }
  if(orientation==1){
      glBegin(GL_LINE_LOOP);
        glVertex2d(gx,gy);
        glVertex2d(gx+gheight,gy);
        glVertex2d(gx+gheight,gy-gwidth);
        glVertex2d(gx,gy-gwidth);
      glEnd();
      glFlush();
      glBegin(GL_LINE_STRIP);
        glVertex2d(gx,gy-gwidth);
        glVertex2d(gx+gheight,gy);
      glEnd();
      glFlush();
    }
  if(orientation==2){
    glBegin(GL_LINE_LOOP);
      glVertex2d(gx,gy);
      glVertex2d(gx-gwidth,gy);
      glVertex2d(gx-gwidth,gy-gheight);
      glVertex2d(gx,gy-gheight);
    glEnd();
    glFlush();
    glBegin(GL_LINE_STRIP);
      glVertex2d(gx-gwidth,gy);
      glVertex2d(gx,gy-gheight);
    glEnd();
    glFlush();
  }
  if(orientation==3){
    glBegin(GL_LINE_STRIP);
      glVertex2d(gx,gy);
      glVertex2d(gx,gy+gheight);
      glVertex2d(gx-gwidth,gy+gheight);
      glVertex2d(gx-gwidth,gy);
    glEnd();
    glFlush();
    glBegin(GL_LINE_STRIP);
      glVertex2d(gx,gy+gheight);
      glVertex2d(gx-gwidth,gy);
    glEnd();
    glFlush();
  }
  glEnd();
  glFlush();
}

void myKeyboard(unsigned char key, int mousex, int mousey){
  switch(key){
    case 'n':
    orientation=(++orientation)%4;
    // std::cout<<orientation<<std::endl;
    if(gwidth<1 || gheight<1){
      std::cout << "Height or width is smaller than 1 pixel." << std::endl;
      //program will continue to output this after height or width is smaller than one
    }
    else if(orientation==0){
      bottomleft(gx,gy,gwidth,gheight);
      glutPostRedisplay();
      // orientation=2;
    }
    else if(orientation==1){
      // gy=gy+gheight;
      topleft(gx,gy,gwidth,gheight);
      glutPostRedisplay();
    }
    else if(orientation==2){
      topright(gx,gy,gwidth,gheight);
      glutPostRedisplay();
    }
    else if(orientation==3){
      bottomright(gx,gy,gwidth,gheight);
      glutPostRedisplay();
    }
    break;
    case 'e':
    exit(0);
  }
}

  int main(int argc, char* argv[])
  {
    std::cout << "n: Next rectangle" << std::endl;
    std::cout << "e: Exit" << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Golden Rectangle");
    glClear(GL_COLOR_BUFFER_BIT);
    glutKeyboardFunc(myKeyboard);
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
  }
