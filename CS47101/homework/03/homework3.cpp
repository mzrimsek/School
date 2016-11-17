//Mike Zrimsek
//Computer Graphics
//Homework 3

#include <stdlib.h>
#include <GL/glut.h>

GLfloat mat_specular[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat mat_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 1.0, 1.0, 0.1, 1.0 };
GLfloat default_emission[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light[] = { 1.0, 1.0, 1.0 };

GLfloat sphereA_color[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat sphereB_color[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat sphereC_color[] = { 0.0, 0.0, 1.0, 1.0 };

GLfloat light0_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light1_position[] = { -1.0, -1.0, -1.0, 0.0 };
GLfloat light2_position[] = { 0.0, -1.0, 0.0, 0.0 };

void createLightSource(GLenum lightSource, const GLfloat *lightPosition)
{
    glLightfv(lightSource, GL_DIFFUSE, light);
    glLightfv(lightSource, GL_SPECULAR, light);
    glLightfv(lightSource, GL_POSITION, lightPosition);
}

void createSphere(GLenum lightSource1, GLenum lightSource2, const GLfloat *sphereColor)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sphereColor);
    glEnable(lightSource1);
    glEnable(lightSource2);
    glutSolidSphere(0.4, 20, 16);
    glPopMatrix();
    glDisable(lightSource1);
    glDisable(lightSource2);
}

void init(void)
{
    GLfloat lmodel_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    createLightSource(GL_LIGHT0, light0_position);
    createLightSource(GL_LIGHT1, light1_position);
    createLightSource(GL_LIGHT2, light2_position);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
    glTranslatef(0.75, -0.5, 0.0);
    createSphere(GL_LIGHT0, GL_LIGHT1, sphereA_color);
    
    glTranslatef(-0.75, -0.5, 0.0);
    createSphere(GL_LIGHT1, GL_LIGHT2, sphereB_color);    
    
    glTranslatef(0.75, 1.0, 0.0);
    createSphere(GL_LIGHT0, GL_LIGHT2, sphereC_color);
    
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5*(GLfloat)w / (GLfloat)h, 1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
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
