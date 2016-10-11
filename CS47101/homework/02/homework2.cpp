// Mike Zrimsek
// Computer Graphics
// Homework 2

#include <GL/glut.h>

static int WINDOW_WIDTH = 500;
static int WINDOW_HEIGHT = 500;

static int mainMenuId;
static int mainMenuSelection;

void mainMenu(int value)
{
  mainMenuSelection = value;
  glutPostRedisplay();
}

void createMainMenu()
{
  mainMenuId = glutCreateMenu(mainMenu);
  glutAddMenuEntry("Rectangles", 1);
  glutAddMenuEntry("Circle", 2);
  glutAddMenuEntry("Rubberbanding Circle", 3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 27:
      exit(0);
  }
  glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  if(mainMenuSelection == 1)
  {
    glBegin(GL_POLYGON);
      glColor3f(1.0, 0.0, 0.0);
      glVertex2f(-0.25, -0.25);

      glColor3f(1.0, 0.0, 0.0);
      glVertex2f(-0.25, 0.25);

      glColor3f(1.0, 0.0, 0.0);
      glVertex2f(0.5, 0.25);

      glColor3f(1.0, 0.0, 0.0);
      glVertex2f(0.5, -0.25);
    glEnd();
  }
  else if(mainMenuSelection == 2)
  {

  }
  else if(mainMenuSelection == 3)
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
  glutKeyboardFunc(keyboard);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glutDisplayFunc(display);

  glutMainLoop();
  return 0;
}
