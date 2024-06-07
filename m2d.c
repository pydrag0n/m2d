#include <Windows.h>
#define GLUT_NO_LIB_PRAGMA
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>



#define width   1000
#define height  600
#define centerX width/2
#define centerY height/2


int sqMap = 1;
int px, py, ps, pSize; // player x/y // player speed
int pmx, pmy, pSight; // player sight
pmx = centerX;
pmy = centerY;

pSight = 100;  
px = centerX;
py = centerY;
ps = 10;
pSize = 10;
int sqSize=40;

void GenerateMap() {
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);

    glVertex2i(400, 400);
    glVertex2i(400+100, 400);
    glVertex2i(400+100, 400-100);
    glVertex2i(400, 400-100);


    glEnd();

}

void resize() {
    glutReshapeWindow(width, height);
}

void KV() {
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(1);
    glBegin(GL_LINES);

    for(int i=0; i<=width; i+=sqSize){
        glVertex2i(i, 0);
        glVertex2i(i, width);
        glVertex2i(0, i);
        glVertex2i(width, i);
    }
    glEnd();
}

void drawPlayer() {
    glColor3f(1, 1, 1);
    glPointSize(pSize);
    glBegin(GL_POINTS);
    glVertex2i(px, py);
    glEnd();
}

void drawPSight() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(1);
    glBegin(GL_LINES);

    glVertex2i(px, py);
    glVertex2i(pmx, pmy);
    glEnd();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(sqMap){KV();}
    drawPSight();
    GenerateMap();

    drawPlayer();
    glutSwapBuffers();

}

void regularSqSize(unsigned char key, int x, int y) {

    switch (key) {

        case 'b': //upsize
            if (!sqMap){break;}
            sqSize+=5;
            break;

        case 'v': //downsize
            if (!sqMap){break;}
            if (sqSize<=5) {
                sqSize=5;
                break;
            }
            sqSize-=1;
            break;

        case 'r': // reset
            if (!sqMap){break;}
            sqSize=40;
            break;

    // PLAYER KEYBOARD
        case 'w':
            py-=ps;
            pmx = px;
            pmy = py-pSight;

            break;

        case 's':
            py+=ps;
            pmx = px;
            pmy = py+pSight;
            
            break;

        case 'a':
            px-=ps;
            pmx = px-pSight;
            pmy = py;
            break;

        case 'd':
            px+=ps;
            pmx = px+pSight;
            pmy = py;
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