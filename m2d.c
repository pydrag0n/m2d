#include <Windows.h>
#define GLUT_NO_LIB_PRAGMA
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>



#define width   1200
#define height  700
#define centerX width/2
#define centerY height/2
#define mapX 25
#define mapY 15
#define mapS 40 //size of one block

typedef struct {
    int x, y; // координаты левого верхнего угла
    int sideLength; // длина стороны квадрата
} Square;


int sqMap = 0; // 0 or 1
int px, py, ps, pSize; // player x/y // player speed
int pmx, pmy, pSight; // player sight


int spwn = 1;
pSight = 100;  
px = centerX;
py = centerY;
int pPosX, pPosY;
pmx = centerX;
pmy = centerY;
ps = 41;
pSize = 40;
int sqSize=40;
int d =20;
int map[mapY][mapX] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
};


void resize() {
    glutReshapeWindow(width, height);
}

void drawPlayer() {

    glColor3f(1, 1, 1);
    glPointSize(pSize);
    glBegin(GL_POINTS);
    glVertex2i(px, py);

    glEnd();
}
void drawMap() {

    int xo, yo;
    xo = 0;
    yo = 80;

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    for (int y=0; y<mapY; y++) {

        for (int x=0; x<mapX; x++) {
            xo+=mapS+1;
            
            if (map[y][x]==1) {
                glColor3f(0,1,1);
            }
            else if (map[y][x]==2 && spwn==1) {
                px=xo+20;
                py=yo+20+1;
                pPosY=y;
                pPosX=x;
                spwn=0; 
            }  
            else {      
                glColor3f(0,0,0);
            }

            glVertex2i(xo, yo);
            glVertex2i(xo+mapS, yo);
            glVertex2i(xo+mapS, yo-mapS);
            glVertex2i(xo, yo-mapS);

        }
        yo+=mapS+1;
        xo=0;

    }
    glEnd();
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
    glColor3f(1.0, 1.0, 1.0); 
    drawMap();
    drawPSight();
    drawPlayer();
    glutSwapBuffers();
    _sleep(1);
    glutPostRedisplay();

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
                sqSize-=5;
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
            if(map[pPosY-1][pPosX]==1) {break;}
            map[pPosY][pPosX] = 0;
            pPosY-=1;
            map[pPosY][pPosX] = 2;
            py-=ps;
            pmx = px;
            pmy = py-pSight;

            break;

        case 's':
            if(map[pPosY+1][pPosX]==1) {break;}
            map[pPosY][pPosX] = 0;
            pPosY+=1;
            map[pPosY][pPosX] = 2;
            py+=ps;
            pmx = px;
            pmy = py+pSight;
            break;

        case 'a':
            if(map[pPosY][pPosX-1]==1) {break;}
            map[pPosY][pPosX] = 0;
            pPosX-=1;
            map[pPosY][pPosX] = 2;
            px-=ps;
            pmx = px-pSight;
            pmy = py;

            break;

        case 'd':
            if(map[pPosY][pPosX+1]==1) {break;}
            map[pPosY][pPosX] = 0;
            pPosX+=1;
            map[pPosY][pPosX] = 2;

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