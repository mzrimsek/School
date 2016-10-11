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

static int SQUARE_MENU_SELECTION = 1;
static int CIRCLE_MENU_SELECTION = 2;
static int RUBBERBANDING_CIRCLE_MENU_SELECTION = 3;

int square_x, square_y;
double square_size = 20.0;

double circle_x = 50, circle_y = 50;
double circle_radius = 50;
int circle_change = 7;

double rubber_circle_tracking = 0;
double rubber_circle_start_x, rubber_circle_start_y;
double rubber_circle_end_x, rubber_circle_end_y;

void mainMenu(int value)
{
  mainMenuSelection = value;
  glutPostRedisplay();
}

void createMainMenu()
{
  mainMenuId = glutCreateMenu(mainMenu);
  glutAddMenuEntry("Square", SQUARE_MENU_SELECTION);
  glutAddMenuEntry("Circle", CIRCLE_MENU_SELECTION);
  glutAddMenuEntry("Rubberbanding Circle", RUBBERBANDING_CIRCLE_MENU_SELECTION);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void startMotion(int x, int y)
{
  rubber_circle_tracking = 1;

  rubber_circle_start_x = x;
  rubber_circle_start_y = WINDOW_HEIGHT - y;

  rubber_circle_end_x = x;
  rubber_circle_end_y = WINDOW_HEIGHT - y;
}

void stopMotion(int x, int y)
{
  rubber_circle_tracking = 0;

  rubber_circle_end_x = x;
  rubber_circle_end_y = WINDOW_HEIGHT - y;
}

void mouseCallback(int btn, int state, int x, int y)
{
  if(btn == GLUT_LEFT_BUTTON)
	{
    if(state == GLUT_DOWN) startMotion(x, y);
    if(state == GLUT_UP) stopMotion(x, y);
	}
  glutPostRedisplay();
}

void trackSquareLocation(int x, int y)
{
  square_x = x;
  square_y = WINDOW_HEIGHT - y;
}

void mouseMotionCallback(int x, int y)
{
  if(mainMenuSelection == SQUARE_MENU_SELECTION)
  {
    trackSquareLocation(x, y);
    glColor3f(1.0, 0.0, 0.0);
  }
  if(mainMenuSelection == RUBBERBANDING_CIRCLE_MENU_SELECTION)
  {
    if(rubber_circle_tracking)
    {
      rubber_circle_end_x = x;
      rubber_circle_end_y = WINDOW_HEIGHT - y;
    }
  }
  glutPostRedisplay();
}

void mousePassiveMotionCallback(int x, int y)
{
  if(mainMenuSelection == SQUARE_MENU_SELECTION)
  {
    trackSquareLocation(x, y);
    glColor3f(1.0, 1.0, 0.0);
  }
  glutPostRedisplay();
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
    if(circle_x > WINDOW_WIDTH - circle_radius || circle_y > WINDOW_HEIGHT - circle_radius 
    || circle_x < circle_radius || circle_y < circle_radius)
    {
      circle_change *= -1;
    }
    circle_x += circle_change;
    circle_y += circle_change;
  }
  glutPostRedisplay();
}

void drawSquare(int x, int y)
{
  glTranslatef(x, y, 0.0);
  glBegin(GL_POLYGON);
    glVertex2f(square_size, square_size);
    glVertex2f(-square_size, square_size);
    glVertex2f(-square_size, -square_size);
    glVertex2f(+square_size, -square_size);
  glEnd();
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

void reshapeCallback(int width, int height)
{
  WINDOW_WIDTH = width;
  WINDOW_HEIGHT = height;
}

void displayCallback()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if(mainMenuSelection == SQUARE_MENU_SELECTION)
  {
    drawSquare(square_x, square_y);
  }
  else if(mainMenuSelection == CIRCLE_MENU_SELECTION)
  {
    glColor3f(0.0, 0.0, 1.0);
    drawCircle(circle_x, circle_y, circle_radius);
  }
  else if(mainMenuSelection == RUBBERBANDING_CIRCLE_MENU_SELECTION)
  {
    double rubber_circle_radius = rubber_circle_end_x - rubber_circle_start_x;
    
    glColor3f(0.0, 1.0, 0.0);
    drawCircle(rubber_circle_start_x, rubber_circle_start_y, 1);
    if(rubber_circle_tracking)
    {
      glColor3f(1.0, 1.0, 1.0);
      drawCircle(rubber_circle_start_x, rubber_circle_start_y, rubber_circle_radius);
    }
    else
    {
      glColor3f(0.0, 1.0, 0.0);
      drawCircle(rubber_circle_start_x, rubber_circle_start_y, rubber_circle_radius);
    }
  }
  glutSwapBuffers();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Homework 2");

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();  

  createMainMenu();
  glutMouseFunc(mouseCallback);
  glutKeyboardFunc(keyboardCallback);
  glutMotionFunc(mouseMotionCallback);
  glutPassiveMotionFunc(mousePassiveMotionCallback);
  glutIdleFunc(idleCallback);
  glutDisplayFunc(displayCallback);
  glutReshapeFunc(reshapeCallback);

  glutMainLoop();
  return 0;
}
