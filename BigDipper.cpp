#include "globalgl.h"
#include "Utils.h"
#include <fstream>
#include <string>

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
 void myInit(void)
 {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.5f, 0.5f, 0.0f);
    glPointSize(4.0);
    setWorldWin(0.0,640,0.0,480);
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
// the redraw function
void myDisplay(int x, int y)
{
	                 // send all output to display
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  string point, name;
  int x,y;
  fstream fin;

	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
	glutInitWindowSize(640,480);     // set the window size
	glutInitWindowPosition(100, 150); // set the window position on the screen
	glutCreateWindow("Big Dipper");
  fin.open(argv);
  if(fin.fail()){
    cout << "File " << argv << " failed to open" << endl;
  }
  else{
    while(getline(fin,point)){
      if(s.length()==0){
        continue;
      }
      else{
        istringstream is(s);
        is>>point;
        if(is>>name>>x>>y){
          glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
        	glBegin(GL_POINTS);
        		glVertex2i(x,y);         // draw some points (don't know how many)
        	glEnd();
        	glFlush();
        }
      }
    }
  }
   // open the screen window(with its exciting title)
	   // register the redraw function
	myInit();
	glutMainLoop(); 		     // go into a perpetual loop
}
