// Mike Zrimsek
// Computer Graphics
// Homework 2

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

static int WINDOW_WIDTH = 500;
static int WINDOW_HEIGHT = 500;
static double DEGREE_TO_RADIAN = 3.14159/180;

int mainMenuId;
int mainMenuSelection = 0;

static int RECTANGLES_MENU_SELECTION = 1;
static int CIRCLE_MENU_SELECTION = 2;
static int RUBBERBANDING_CIRCLE_MENU_SELECTION = 3;

double circle_x = -0.6, circle_y = -0.6;

void mainMenu(int value)
{
  mainMenuSelection = value;
  glutPostRedisplay();
}

void createMainMenu()
{
  mainMenuId = glutCreateMenu(mainMenu);
  glutAddMenuEntry("Rectangles", RECTANGLES_MENU_SELECTION);
  glutAddMenuEntry("Circle", CIRCLE_MENU_SELECTION);
  glutAddMenuEntry("Rubberbanding Circle", RUBBERBANDING_CIRCLE_MENU_SELECTION);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouseCallback(int btn, int state, int x, int y)
{

}

void mouseMotionCallback(int x, int y)
{

}

void keyboardCallback(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 27:
      exit(0);
  }
  glutPostRedisplay();
}

void idleCallback()
{
  if(mainMenuSelection == CIRCLE_MENU_SELECTION)
  {
    double circleStep = .0001;
    circle_x += circleStep;
    circle_y += circleStep;
  }
  
  glutPostRedisplay();
}

void drawCircle(double x, double y, double radius)
{
  glBegin(GL_LINE_LOOP);
    for(double i = 0; i < 360; i++)
    {
      double degreeInRadian = i*DEGREE_TO_RADIAN;
      glVertex2f(x+cos(degreeInRadian)*radius, y+sin(degreeInRadian)*radius);
    }
  glEnd();
}

void displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT);

  if(mainMenuSelection == RECTANGLES_MENU_SELECTION)
  {
    //red rectangle moves with mouse when left click is down
    glBegin(GL_POLYGON);
      glColor3f(1.0, 0.0, 0.0);
      glVertex2f(0.33, 0.75);
      glVertex2f(0.33, 0.25);
      glVertex2f(0.66, 0.25);
      glVertex2f(0.66, 0.75);
    glEnd();

    //yellow rectangle moves with mouse
    glBegin(GL_POLYGON);
      glColor3f(1.0, 1.0, 0.0);
      glVertex2f(-0.75, -0.75);
      glVertex2f(-0.75, -0.25);
      glVertex2f(0.25, -0.25);
      glVertex2f(0.25, -0.75);
    glEnd();
  }
  else if(mainMenuSelection == CIRCLE_MENU_SELECTION)
  {
    glColor3f(0.0, 0.0, 1.0);
    drawCircle(circle_x, circle_y, 0.25);
  }
  else if(mainMenuSelection == RUBBERBANDING_CIRCLE_MENU_SELECTION)
  {
    
  }

  glFlush();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Homework 2");

  createMainMenu();
  glutMouseFunc(mouseCallback);
  glutMotionFunc(mouseMotionCallback);
  glutKeyboardFunc(keyboardCallback);
  glutIdleFunc(idleCallback);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glutDisplayFunc(displayCallback);

  glutMainLoop();
  return 0;
}
