// Mike Zrimsek
// Computer Graphics
// Homework 2

#include <GL/glut.h>

static int WINDOW_WIDTH = 500;
static int WINDOW_HEIGHT = 500;

void myDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glFlush();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Homework 2");

  glutDisplayFunc(myDisplay);

  glutMainLoop();
}
