#ifndef DESUTILS_H
#define DESUTILS_H

// This will sleep for ms milliseconds.  It calls nanosleep().
void delay(int ms);

extern void setWorldWin(GLdouble left,GLdouble right,
	GLdouble bottom,GLdouble top);

extern void setViewPort(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top);

#endif
