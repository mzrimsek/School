// Mike Zrimsek
// Computer Graphics
// Homework 2

#include <GL/glut.h>

static int WINDOW_WIDTH = 500;
static int WINDOW_HEIGHT = 500;

static int mainMenuId;

void myDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glFlush();
}

void mainMenu(int value)
{

}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Homework 2");

  glutDisplayFunc(myDisplay);

  mainMenuId = glutCreateMenu(mainMenu);
  glutAddMenuEntry("Rectangles", 1);
  glutAddMenuEntry("Circle", 2);
  glutAddMenuEntry("Rubberbanding Circle", 3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}
