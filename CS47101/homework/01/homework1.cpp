#include <GL/glut.h>

void init()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 1.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void myDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT);
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
  glFlush();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Homework 1");

  glutDisplayFunc(myDisplay);

  init();

  glutMainLoop();
}
