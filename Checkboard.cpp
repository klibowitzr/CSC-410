#include "globalgl.h"
#include "Utils.h"

const GLint WINSIZE=800;
GLint size=WINSIZE/8;

void myInit(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   glPointSize(4.0);
   setWorldWin(0.0,WINSIZE,0.0,WINSIZE);
}


void myDisplay(void){
  glClear(GL_COLOR_BUFFER_BIT);
  GLint x,y;
  for(y=0; y<8; y++){
    for(x=0; x<8; x++){
      if((x+y)%2==0){
        glColor3f(0.78, 0.0, 0.22);
      }
      else{
        glColor3f(0.9, 0.45, 0.35);
      }
      glRecti(x*size, y*size, x*size+size, y*size+size);

    }
    x=0;
  }
  glEnd();
  glFlush();
}

int main(int argc, char* argv[])
{
    void (*displaythis)(void);
    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WINSIZE,WINSIZE);
  	glutInitWindowPosition(100, 150);
  	glutCreateWindow("Checkerboard");
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(myDisplay);

  	myInit();
  	glutMainLoop();
}
