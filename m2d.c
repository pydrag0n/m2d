#include <Windows.h>
#define GLUT_NO_LIB_PRAGMA
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
//  off covnocode

// window
#define WIDTH       1200
#define HEIGHT      700
#define CENTER_X    WIDTH/2
#define CENTER_Y    HEIGHT/2

// map
#define MAP_X       34
#define MAP_Y       25 
#define BLOCK_SIZE  20 // size of one block
#define GAP         1  // the gap between the blocks
#define DEBUG       0 // debug mode 1/0 (on/off)


// player 
typedef struct {

    unsigned int    x;
    unsigned int    y;
    unsigned int    step;
    unsigned int    size;
    _Bool           isSpawned;

} Player;
Player P;

// PSIGHT
typedef struct {
    int             x;
    int             y;
    int             length;
    int             condition;
} Sight;
Sight PSight;


sqMap=0;
int                 pPosX; 
int                 pPosY;
int                 sqSize=40;

int map[MAP_Y][MAP_X] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
};


void init() {

    // --------------------------------------
    // PLAYER
    // --------------------------------------
    P.x = 0;
    P.y = 0;
    P.step = BLOCK_SIZE+GAP;
    P.size = BLOCK_SIZE;
    P.isSpawned = TRUE;


    // --------------------------------------
    // SIGHT
    // --------------------------------------
    PSight.x = P.x;
    PSight.y = P.y;
    PSight.length = BLOCK_SIZE;
    PSight.condition = 1; // 1 2 3 4


    // --------------------------------------
    // SHOOTING
    // --------------------------------------



    // --------------------------------------
    // DEBUG MODE
    // --------------------------------------
    if (DEBUG) {
        int sqMap=1;
        // ...
    }

}


void resize() {
    glutReshapeWindow(WIDTH, HEIGHT);
}

void drawPlayer() {

    glColor3f(1, 1, 1);
    glPointSize(P.size);
    glBegin(GL_POINTS);
    glVertex2i(P.x, P.y);

    glEnd();
}
void drawMap() {

    int xo, yo;
    xo = 0;
    yo = 0+BLOCK_SIZE;

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    for (int y=0; y<MAP_Y; y++) {
        for (int x=0; x<MAP_X; x++) {
            xo+=BLOCK_SIZE+GAP;
            if (map[y][x]==1) {
                glColor3f(0,1,1);
            }

            else if (map[y][x]==2 && P.isSpawned==TRUE) {
                P.x = xo+BLOCK_SIZE/2;
                P.y = yo+BLOCK_SIZE/2+GAP;
                pPosY = y+GAP;
                pPosX = x;
                P.isSpawned = FALSE; 
            }
            else if (map[y][x]==3) {
                glColor3f(0.5, 0.5, 1.0);
            }

            else {      
                glColor3f(0,0,0);
            }

            glVertex2i(xo, yo);
            glVertex2i(xo+BLOCK_SIZE, yo);
            glVertex2i(xo+BLOCK_SIZE, yo-BLOCK_SIZE);
            glVertex2i(xo, yo-BLOCK_SIZE);

        }
        yo+=BLOCK_SIZE+GAP;
        xo=0;

    }
    glEnd();
}

void KV() {
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(1);
    glBegin(GL_LINES);

    for(int i=0; i<=WIDTH; i+=sqSize){
        glVertex2i(i, 0);
        glVertex2i(i, WIDTH);
        glVertex2i(0, i);
        glVertex2i(WIDTH, i);
    }
    glEnd();
}



void drawPSight() {

    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(P.x, P.y);
    glVertex2i(PSight.x, PSight.y);

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

void moveUp() {
    P.y -= P.step;
    PSight.x = P.x;
    PSight.y = P.y-PSight.length;

    map[pPosY][pPosX] = 0;
    pPosY-=1;
    map[pPosY][pPosX] = 2;

}
void moveDown() { 
    P.y += P.step;
    PSight.x = P.x;
    PSight.y = P.y+PSight.length;
    map[pPosY][pPosX] = 0;
    pPosY+=1;
    map[pPosY][pPosX] = 2;
}

void moveLeft() {
    P.x -= P.step;
    PSight.x = P.x-PSight.length;
    PSight.y = P.y;
    map[pPosY][pPosX] = 0;
    pPosX-=1;
    map[pPosY][pPosX] = 2;
}

void moveRight() {
    P.x += P.step;
    PSight.x = P.x+PSight.length;
    PSight.y = P.y;
    map[pPosY][pPosX] = 0;
    pPosX+=1;
    map[pPosY][pPosX] = 2;
}


void KeyboardWork(unsigned char key, int x, int y) {
    // --------------------------------------
    // DEBUG
    // --------------------------------------
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


    // --------------------------------------
    // PLAYER KEYBOARD
    // --------------------------------------
        case 'w':

            if(map[pPosY-1][pPosX]==1) {break;}
            moveUp();
            break;


        case 's':

            if(map[pPosY+1][pPosX]==1) {break;}
            moveDown();
            break;

        case 'a':
            if(map[pPosY][pPosX-1]==1) {break;}
            moveLeft();
            break;

        case 'd':

            if(map[pPosY][pPosX+1]==1) {break;}
            moveRight();
            break;
    }
        //     case 'f':
        //     if (PSight.condition==1) {
        //         map[pPosY][pPosX]=3;
        //         break;
        // }

    glutPostRedisplay();


}


void MouseWork(int button, int state, int x, int y) {
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
        switch(PSight.condition) {
            case 1:
                if(map[pPosY-1][pPosX]==1 || map[pPosY-1][pPosX]==2 || map[pPosY-1][pPosX]==3) {break;}
                map[pPosY-1][pPosX]=3;
                break;
            case 2:
                if(map[pPosY+1][pPosX]==1 || map[pPosY+1][pPosX]==2 || map[pPosY+1][pPosX]==3) {break;}
                map[pPosY+1][pPosX]=3;
                break;
            case 3:
                if(map[pPosY][pPosX-1]==1 || map[pPosY][pPosX-1]==2 || map[pPosY][pPosX-1]==3) {break;}
                map[pPosY][pPosX-1]=3;
                break;
            case 4:
                if(map[pPosY][pPosX+1]==1 || map[pPosY][pPosX+1]==2 || map[pPosY][pPosX+1]==3) {break;}
                map[pPosY][pPosX+1]=3;
                break;
        }
    }
    else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) {
        switch(PSight.condition) {
            case 1:
                if(map[pPosY-1][pPosX]==1 || map[pPosY-1][pPosX]==2 || map[pPosY-1][pPosX]==0) {break;}
                map[pPosY-1][pPosX]=0;
                break;
            case 2:
                if(map[pPosY+1][pPosX]==1 || map[pPosY+1][pPosX]==2 || map[pPosY+1][pPosX]==0) {break;}
                map[pPosY+1][pPosX]=0;
                break;
            case 3:
                if(map[pPosY][pPosX-1]==1 || map[pPosY][pPosX-1]==2 || map[pPosY][pPosX-1]==0) {break;}
                map[pPosY][pPosX-1]=0;
                break;
            case 4:
                if(map[pPosY][pPosX+1]==1 || map[pPosY][pPosX+1]==2 || map[pPosY][pPosX+1]==0) {break;}
                map[pPosY][pPosX+1]=0;
                break;
        }
    }

}


void SpecialKeyboardWork(int key, int x, int y) {
    switch (key)
    {
        case GLUT_KEY_UP:
            PSight.x = P.x;
            PSight.y = P.y-PSight.length;
            PSight.condition = 1;
            break;
        case GLUT_KEY_DOWN:
            PSight.x = P.x;
            PSight.y = P.y+PSight.length;
            PSight.condition = 2;
            break;
        case GLUT_KEY_LEFT:
            PSight.x = P.x-PSight.length;
            PSight.y = P.y;
            PSight.condition = 4;
            break;
        case GLUT_KEY_RIGHT:
            PSight.x = P.x+PSight.length;
            PSight.y = P.y;
            PSight.condition = 4;
            break;
    }
}


int main(int argc, char* argv[]) {
    init();
    int winPosX, winPosY;
    winPosX = 30;
    winPosY = 30;


    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(winPosX, winPosY);
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("m2d");
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, WIDTH, HEIGHT, 0); 
    glutReshapeFunc(resize);
    glutDisplayFunc(render);
    glutKeyboardFunc(KeyboardWork);
    glutMouseFunc(MouseWork);
    glutSpecialFunc(SpecialKeyboardWork);
    glutPostRedisplay();
    _sleep(1);
    glutMainLoop();

    return 0;
}