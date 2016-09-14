#include <GL/glut.h>

static int WINDOW_WIDTH = 500;
static int WINDOW_HEIGHT = 500;

void init()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 1.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

//rainbow square
void bottomLeftPolygon()
{
  glViewport(0, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

  glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.5, -0.5);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-0.5, 0.5);

    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.5, 0.5);

    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(0.5, -0.5);
  glEnd();
}

//blue square
void bottomRightPolygon()
{
  glViewport(WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

  glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(-0.5, -0.5);

    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(-0.5, 0.5);

    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.5, 0.5);

    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.5, -0.5);
  glEnd();
}

//green square
void topLeftPolygon()
{
  glViewport(0, WINDOW_HEIGHT/2, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

  glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-0.5, -0.5);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-0.5, 0.5);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.5, 0.5);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.5, -0.5);
  glEnd();
}

//red square
void topRightPolygon()
{
  glViewport(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

  glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.5, -0.5);

    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.5, 0.5);

    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.5, 0.5);

    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.5, -0.5);
  glEnd();
}

void myDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT);

  bottomLeftPolygon();
  bottomRightPolygon();
  topLeftPolygon();
  topRightPolygon();

  glFlush();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Homework 1");

  glutDisplayFunc(myDisplay);

  init();

  glutMainLoop();
}
