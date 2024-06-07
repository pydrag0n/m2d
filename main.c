#include <stdlib.h>
#include <Windows.h>
#define GLUT_NO_LIB_PRAGMA
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533 // one deg in rad
#define mapX 8
#define mapY 8
#define mapS 64 //size of one block

float px, py, pdx, pdy, pa; // player pos, delta, angle
int map[]=
{
    1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1
};

void DrawMap2D()
{
    int x, y, xo, yo;
    for (y = 0; y < mapY; y++) {
        for (x = 0; x < mapX; x++) {
            if(map[y * mapX + x] == 1) {
                glColor3f(1, 1, 1);
            } else {
                glColor3f(0, 0, 0);
            }
            xo = x * mapS;
            yo = y * mapS;
            glBegin(GL_QUADS);
            glVertex2i(xo        + 1, yo        + 1);
            glVertex2i(xo        + 1, yo + mapS - 1);
            glVertex2i(xo + mapS - 1, yo + mapS - 1);
            glVertex2i(xo + mapS - 1, yo        + 1);
            glEnd();
        }
    }
}

void DrawPlayer()
{
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(px, py);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px + pdx * 5, py + pdy * 5);
    glEnd();
}

void buttonsMove(unsigned char key, int x, int y)
{
    switch (key) {
        case 'w':
            px += pdx;
            py += pdy;
            break;
        case 's':
            px -= pdx;
            py -= pdy;
            break;
    }
    glutPostRedisplay();
}

void buttonsRotate(int key, int x, int y)
{
    switch (key) { 
        case GLUT_KEY_LEFT:
            pa -= 0.1;
            if(pa < 0) {pa += 2*PI;}
            pdx = cos(pa)*5;
            pdy = sin(pa)*5;
            break;
        case GLUT_KEY_RIGHT:
            pa += 0.1;
            if(pa > 2*PI) {pa -= 2*PI;}
            pdx = cos(pa)*5;
            pdy = sin(pa)*5;
            break;

    }
    glutPostRedisplay();
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawMap2D();
    DrawPlayer();
    glutSwapBuffers();
}

void resize()
{
    glutReshapeWindow(1024, 512);
}


void init()
{
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 1024, 512, 0);
    px = 300;
    py = 300;
    pdx = cos(pa)*5;
    pdy = sin(pa)*5;
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 512);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Ray");
    init();
    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutSpecialFunc(buttonsRotate);
    glutKeyboardFunc(buttonsMove);
    glutMainLoop();
}