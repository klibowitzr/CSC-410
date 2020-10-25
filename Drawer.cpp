#include "globalgl.h"
#include "Utils.h"
#include <vector>
#include <iostream>
#include <fstream>
std::vector<int> xcoords, ycoords, pointx, pointy;
std::vector<int>::iterator itx, ity, px, py;
std::fstream file;
GLint connect=0;

void getpoints(void){
  file.open("polyline.txt",std::fstream::app);
  for(itx=pointx.begin(),ity=pointy.begin();itx!=pointx.end() && ity!=pointy.end(); itx+=2, ity+=2){
    file << *itx << " " << *ity << std::endl;
  }
    file.close();
}
const GLint WINSIZE=800;
void myInit(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   glPointSize(10.0);
   setWorldWin(0.0,WINSIZE,0.0,WINSIZE);
}
void myDisplay(void){
  glClear(GL_COLOR_BUFFER_BIT);
  if(xcoords.size()>1){
    glBegin(GL_LINE_STRIP);
    for(itx=xcoords.begin(), ity=ycoords.begin(); itx!=xcoords.end() && ity!=ycoords.end(); ++ity, ++itx){
      glVertex2i(*itx,*ity);
      glVertex2i(*itx+1,*ity+1);
    }
    glEnd();
    glFlush();
  }
  if(pointx.size()>1){
    glBegin(GL_POINTS);
    for(px=pointx.begin(), py=pointy.begin(); px!=pointx.end()&& py!=pointy.end();++px, ++py){
      glVertex2d(*px,*py);
    }
    glEnd();
    glFlush();
  }
  if(connect==1){
    glBegin(GL_LINE_STRIP);
    for(px=pointx.begin(), py=pointy.begin(); px!=pointx.end()&& py!=pointy.end();++px, ++py){
      glVertex2i(*px,*py);
      glVertex2i(*px+1,*py+1);
    }

  }
  glEnd();
  glFlush();
}
void myMouse(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON){
    xcoords.push_back(x);
    ycoords.push_back(WINSIZE-y);

  }
  glutPostRedisplay();
}
void myKeyboard(unsigned char key, int mousex, int mousey){
  GLint x=mousex;
  GLint y=WINSIZE-mousey;
  switch(key){
    case 'p':
      pointx.push_back(x);
      pointy.push_back(y);
      glutPostRedisplay();
      break;
    case 'e':
      getpoints();
      std::cout << "File polyline.txt was successfully created." << std::endl;
      exit(0);
    case 'c':
    connect=1;
    glutPostRedisplay();
    default:
      break;
  }
  glutPostRedisplay();
}
int main(int argc, char* argv[])
{
    void (*displaythis)(void);
    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WINSIZE,WINSIZE);
  	glutInitWindowPosition(100, 150);
  	glutCreateWindow("Drawer");
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutMouseFunc(myMouse);
  	myInit();
  	glutMainLoop();
}
