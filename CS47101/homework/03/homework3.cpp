//Mike Zrimsek
//Computer Graphics
//Homework 3

#include <stdlib.h>
#include <GL/glut.h>

GLfloat mat_specular[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat mat_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 1.0, 1.0, 0.1, 1.0 };
GLfloat default_emission[] = { 0.0, 0.0, 0.0, 1.0 };

//red ball
GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat red_light[] = { 1.0, 1.0, 1.0 };
GLfloat red_light_position[] = { 1.0, 1.0, 1.0, 0.0 };

//blue ball
GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat blue_light[] = { 1.0, 1.0, 1.0 };
GLfloat blue_light_position[] = { 1.0, 1.0, 1.0, 0.0 };

//green ball
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat green_light[] = { 1.0, 1.0, 1.0 };
GLfloat green_light_position[] = { 1.0, 1.0, 1.0, 0.0 };

void init(void)
{
	GLfloat lmodel_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //red light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, red_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, red_light);
	glLightfv(GL_LIGHT0, GL_POSITION, red_light_position);

    //blue light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, blue_light);
	glLightfv(GL_LIGHT1, GL_POSITION, blue_light_position);

    //green light
    glLightfv(GL_LIGHT2, GL_DIFFUSE, green_light);
	glLightfv(GL_LIGHT2, GL_SPECULAR, green_light);
	glLightfv(GL_LIGHT2, GL_POSITION, green_light_position);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

    //red ball
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
	glEnable(GL_LIGHT0);
	glTranslatef(0.75, -0.5, 0.0);
	glutSolidSphere(0.4, 20, 16);
	glPopMatrix();
	glDisable(GL_LIGHT0);

    //blue ball
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
	glEnable(GL_LIGHT1);
	glTranslatef(0.0, 0.5, 0.0);
	glutSolidSphere(0.4, 20, 16);
	glPopMatrix();
	glDisable(GL_LIGHT1);

    //green ball
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
	glEnable(GL_LIGHT2);
	glTranslatef(-0.75, -1.0, 0.0);
	glutSolidSphere(0.4, 20, 16);
	glPopMatrix();
	glDisable(GL_LIGHT2);

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w,
			1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-1.5*(GLfloat)w / (GLfloat)h,
			1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
