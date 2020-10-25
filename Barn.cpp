#include "globalgl.h"
#include "Utils.h"
#include "rklib.h"
#include "camera.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
Mesh barn;
nCamera cam;
double gx = 5.0, gy = 0.0, gz = 0.0;
int yrot = 0;
GLint WIDTH=640, HEIGHT=480, DRAW=0;
GLdouble xview=0, yview=0, zview=3;
std::string fname;

void myInit(void){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(4.0);
  glLineWidth(2.0);
  setWorldWin(0.0,WIDTH,0.0,HEIGHT);
}

void myKeyboardFunc(unsigned char key, int mousex, int mousey){
  //   switch(key){
  //   case 'e':
  //   std::cout << xview << " " << yview << " " << zview << std::endl;
  //   exit(0);
  //   break;
  //   case 'a':
  //   xview-=0.5;
  //   break;
  //   case 'd':
  //   xview+=0.5;
  //   break;
  //   case 's':
  //   yview-=0.5;
  //   break;
  //   case 'w':
  //   yview+=0.5;
  //   break;
  //   case 'z':
  //   zview-=0.5;
  //   break;
  //   case 'c':
  //   zview+=0.5;
  //   break;
  // }
  {
    switch(key) {
        case '\033':
        case 'q':
            exit(0);
        // forward
        case 'F':
            cam.slide(0.0,0.0,0.2);
            break;
        // back
        case 'f':
            cam.slide(-0.0,-0.0,-0.2);
            break;
        //pitch
        case 'P':
            cam.pitch(1.0);
            break;
        //pitch
        case 'p':
            cam.pitch(-1.0);
            break;
        // yaw
        case 'y':
            cam.yaw(-1.0);
            break;
        // yaw
        case 'Y':
            cam.yaw( 1.0);
            break;
        // roll
        case 'R':
            cam.roll( 1.0);
            break;
        // roll
        case 'r':
            cam.roll(-1.0);
            break;
        // case 'T':
        //     rotateTeapot = !rotateTeapot;
        //     break;

        // move camera up
        case 'u':
            gy++;
            break;
        case 'U':
            gy--;
            break;

        case 'w':
            // this flies the camera in a circle around the center
            static int i;
            double d = 5.0;
            gx = d*cos(PI * i / 180.0);
            gz = d*sin(PI * i / 180.0);
            cam.set(gx, gy, gz, 0, 0, 0, 0, 1, 0);
            i = (i + 2) % 360;
            break;
    }
  glutPostRedisplay();
}
void myDisplay(){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  GLfloat mat_ambient[]={0.8f, 0.8f, 0.8f, 1.0f};
  GLfloat mat_diffuse[]={0.6f, 0.6f, 0.6f,1.0f};
  // GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
  GLfloat mat_specular[]={0.5f,0.5f,0.5f,1.0f};

  GLfloat mat_shininess[]={50.0f};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  // GLfloat lightIntensity[]={0.6f, 0.6f, 0.6f, 1.0f};
  GLfloat lightIntensity[]={0.5f, 0.0f, 0.7f, 1.0f};

  // GLfloat light_position[]={2.0f,6.0f,3.0f,0.0f};
  GLfloat light_position[]={20.0,10.0,20,0.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
  GLfloat light_position2[]={-20.0,10.0,20,0.0f};

  glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5,5,-5,5,-5,50);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(xview,yview,zview, 1,1,1,0,1,0);

  // glScaled(40,40,80);
  glPushMatrix();
  glScaled(0.5,0.5,2);
  barn.draw();
  glPopMatrix();
  glFlush();
}
int main(int argc, char* argv[]){
  if(!argv[1]){
    std::cout << "Please provide filename." << std::endl;
    std::cout << "(HINT: Use barn.txt)" << std::endl;
    std::cin>>fname;
  }
  else{
    fname=argv[1];
  }
  barn.init(fname);
  std::cout << "a/d: change eye.x" << std::endl;
  std::cout << "w/s: change eye.y" << std::endl;
  std::cout << "z/c: change eye.z" << std::endl;
  std::cout << "e:exit"<< std::endl;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Barn");
  glClear(GL_COLOR_BUFFER_BIT);
  myInit();
  glutDisplayFunc(myDisplay);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  // glutIdleFunc(idle);
  glutKeyboardFunc(myKeyboardFunc);
  cam.set(gx, gy, gz, 0, 0, 0, 0, 1, 0); // make the initial camera
    cam.setShape(45.0f, 64.0f/48.0f, 0.5f, 50.0f);
  glutMainLoop();

  }
