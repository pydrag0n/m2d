#include <Windows.h>
#define GLUT_NO_LIB_PRAGMA
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>



#define width   800
#define height  800
#define centerX width/2
#define centerY height/2

int sqSize=40;

void resize() {
    glutReshapeWindow(width, height);
}

void KV() {
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(1);
    glBegin(GL_LINES);

    for(int i=0; i<=height; i+=sqSize){
        glVertex2i(i, 0);
        glVertex2i(i, height);
        glVertex2i(0, i);
        glVertex2i(height, i);
    }
    glEnd();
}

void drawPlayer() {
    glColor3f(1, 1, 1);
    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex2i(centerX, centerY);
    glEnd();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(1);
    glBegin(GL_LINES);


    glVertex2i(centerX, centerY);
    glVertex2i(centerX+300, centerY+500);
    glEnd();
    KV();
    drawPlayer();
    glutSwapBuffers();

}

void regularSqSize(unsigned char key, int x, int y) {

    switch (key) {
    case 'x':
        sqSize+=5;
        break;

    case 'z':
        if (!sqSize<=5) {
            sqSize=5;
            break;
        }
        sqSize-=1;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    int winPosX, winPosY;
    winPosX = 30;
    winPosY = 30;


    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(winPosX, winPosY);
    gluOrtho2D(0, width, height, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("m2d");
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, width, height, 0); 
    glutReshapeFunc(resize);
    glutDisplayFunc(render);
    glutKeyboardFunc(regularSqSize);


    glutMainLoop();


    return 0;
}