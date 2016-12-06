#include <GL/glut.h>
#include <cstdlib>

const unsigned int W = 500;
const unsigned int H = 500;
unsigned int data[3][W][H];

void drawM()
{
    //left vert
    for(size_t y = 0; y < 20; y++)
    {
        for(size_t x = 0; x < 100; x++)
        {
            data[0][x][y] = (rand() % 255) * 255 * 255 * 255;
			data[1][x][y] = (rand() % 255) * 255 * 255 * 255;
			data[2][x][y] = (rand() % 255) * 255 * 255 * 255;
        }
    }

    //top horiz
    for(size_t y = 0; y < 80; y++)
    {
        for(size_t x = 100; x < 120; x++)
        {
            data[0][x][y] = (rand() % 255) * 255 * 255 * 255;
			data[1][x][y] = (rand() % 255) * 255 * 255 * 255;
			data[2][x][y] = (rand() % 255) * 255 * 255 * 255;
        }
    }

    //middle small vert
    for(size_t y = 30; y < 50; y++)
    {
        for(size_t x = 50; x < 100; x++)
        {
            data[0][x][y] = (rand() % 255) * 255 * 255 * 255;
			data[1][x][y] = (rand() % 255) * 255 * 255 * 255;
			data[2][x][y] = (rand() % 255) * 255 * 255 * 255;
        }
    }

    //right vert
    for(size_t y = 60; y < 80; y++)
    {
        for(size_t x = 0; x < 100; x++)
        {
            data[0][x][y] = (rand() % 255) * 255 * 255 * 255;
			data[1][x][y] = (rand() % 255) * 255 * 255 * 255;
			data[2][x][y] = (rand() % 255) * 255 * 255 * 255;
        }
    }
}

void drawI()
{
    for(size_t y = 100; y < 120; y++)
    {
        for(size_t x = 0; x < 120; x++)
        {
            data[0][x][y] = (rand() % 255) * 255 * 255 * 255;
			data[1][x][y] = (rand() % 255) * 255 * 255 * 255;
			data[2][x][y] = (rand() % 255) * 255 * 255 * 255;
        }
    }
}

void display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

    drawM();
    drawI();
    
    
	glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_INT, data);
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutCreateWindow("GLUT");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}