

#include <GL/glut.h> 

#include <math.h>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "Cube.h"
#include "Object.h"

using namespace std;

// size of grid side
#define N 20
#define M 4

// width and height of initial window
#define width 500
#define height 500

// window initial location x and y
#define locationx 50
#define locationy 50

GLfloat posx; // camera position on x
GLfloat posy; // camera position on y
GLfloat posz; // camera position on z
GLfloat lookx; // camera points on x
GLfloat looky; // camera points on y
GLfloat lookz; // camera points on z
GLfloat camerax; // camera positioned on x
GLfloat cameray; // camera positioned on y
GLfloat cameraz; // camera positioned on z
GLfloat angley; // camera angle around y axis
GLfloat anglexz; // camera angle around x and z axis
GLfloat zoom; // zoom factor
GLfloat dist; // distance from center (0, 0, 0)

bool objectFound = false; // object found to remove MxMxM where M >= 4
GLint scaleFound; // value of M
GLint x; // x location to start
GLint y; // y location to start
GLint z; // z location to start

GLint points; // user points

GLint speed; // game speed

Object *object = new Object(); // a falling object

GLint cubes[N][N][N]; // game cubes in the game for grid N = 20

// game state enum
enum GAME {
    NOTHING,
    START,
    PAUSE,
    END
};
GAME gameStatus; // initialize game state to nothing


// glut required functions
void initializeVariables();
void drawGame(void);
void grid(void);
void drawCubes();
void resizeGame(int w, int h);
void handleKeyboard(unsigned char key, int x, int y);
void handleKeyboardSpecial(int key, int x, int y);
void printPoints();
void run(int var);
void moveObjectDown();
void moveObjectLeft();
void moveObjectRight();
void moveObjectBack();
void moveObjectForward();
bool checkArrayOfCubes(GLint x, GLint y, GLint z, GLint scale);
void findLargeObject(GLint i1, GLint j1, GLint k1, GLint scale);


/**
 * Start point of application.
 */
int main(int argc, char ** argv) {
    initializeVariables();
    
    // init glut
    glutInit(&argc, argv);
    
    // set window position
    glutInitWindowPosition(locationx, locationy);
    
    // set window size at 500 x 500
    glutInitWindowSize(width, height);
    
    // set display mode
    // 1. Double buffer
    // 2. RGB display
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // create window with title
    glutCreateWindow("Askisi 2 | 2013 - 2014");

    // set black background for window
    glClearColor(0.0,0.0,0.0,0.0);

    // set this for correct depth projection
    glEnable(GL_DEPTH_TEST);
    
    // set callback functions
    glutDisplayFunc(drawGame);
    glutReshapeFunc(resizeGame);
    glutKeyboardFunc(handleKeyboard);
    glutSpecialFunc(handleKeyboardSpecial);
    
    // enter glut main loop
    glutMainLoop();
    
    return 0;
}

/**
 * Initialize variables.
 */
void initializeVariables() {
    angley = 45; // 45 degrees on x axis
    anglexz = 60; // 60 degrees on y axis
    
    zoom = 1.0; // zoom factor
    dist = 55; // distance from center
    
    posx = sin(angley * M_PI / 180) * dist; // camera x location
    posy = cos(anglexz * M_PI / 180) * dist;  // camera x location
    posz = cos(angley * M_PI / 180) * dist;  // camera x location
    
    lookx = 0.0; // where camera points on x
    looky = 0.0; // where camera points on y
    lookz = 0.0; // where camera points on y
    
    camerax = 0.0; // how camera is positioned x
    cameray = 1.0; // how camera is positioned y
    cameraz = 0.0; // how camera is positioned z
    
    points = 0; // initialize points to 0
    
    gameStatus = NOTHING; // initialize game state to nothing
    
    speed = 1000; // initialize game speed to 1 sec
    
    // initialize array of cubes : arxikopoihsh tou plegmatow sintetagmenon oste na einai mideniko
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            for (int k=0; k<N; k++) {
                cubes[i][j][k] = 0;
            }
        }
    }
    
    object->createObject(N);
}

// draw the game
// this function is set as the callback for glut glutDisplayFunc
void drawGame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40 * zoom, width / height, 1.0, 100.0f);
    
    // calculate camera position
    posx = sin(angley * M_PI / 180) * dist; // camera x location
    posy = cos(anglexz * M_PI / 180) * dist;  // camera x location
    posz = cos(angley * M_PI / 180) * dist;  // camera x location
    
    // position the camera
    gluLookAt(posx, posy, posz, lookx, looky, lookz, camerax, cameray, cameraz);

    // create the game grid
    grid();
    
    // draw object
    object->createCubes();
    
    // draw cubes
    drawCubes();
    
    // print points
    printPoints();
    
    // swap buffers
    glutSwapBuffers();
}

// what happens when window is resized
// this function is set as the callback for glut glutReshapeFunc
void resizeGame(int w, int h) {         //kathe fora pou anoigo to parathiro na vlepo tin idia skini kai oxi autin pou afisa prin
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(40 * zoom, (GLfloat) w / (GLfloat) h, 1.0, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// this function creates the grid
// it draws the grid lines for each side of the grid
void grid() {
    
    // white color
    glColor3f(1.0, 1.0, 1.0);
    
    // draw lines
    glBegin(GL_LINES);
    for (int i=0; i<N+1; i++) {
        // x -> (0, N), y -> (i, i), z -> (0, 0)
        glVertex3d(0, i, 0);
        glVertex3d(N, i, 0);
        
        // x -> (0, N), y -> (0, 0), z -> (i, i)
        glVertex3d(0, 0, i);
        glVertex3d(N, 0, i);
        
        // x -> (i, i), y -> (0, N), z -> (0, 0)
        glVertex3d(i, 0, 0);
        glVertex3d(i, N, 0);
        
        // x -> (0, 0), y -> (0, N), z -> (i, i)
        glVertex3d(0, 0, i);
        glVertex3d(0, N, i);
        
        // x -> (i, i), y -> (0, 0), z -> (0, N)
        glVertex3d(i, 0, 0);
        glVertex3d(i, 0, N);

        // x -> (0, 0), y -> (i, i), z -> (0, N)
        glVertex3d(0, i, 0);
        glVertex3d(0, i, N);
    }
    
    // stop drawing lines
    glEnd();
}

// this function will draw all cubes in the game
void drawCubes() {

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            for (int k=0; k<N; k++) {
                if (cubes[i][j][k] == 1) {
                    // set color to blue
                    glColor3f(0.1, 0.5, 0.9);
                    
                    // push current matrix
                    glPushMatrix();
                    
                    // translate location
                    glTranslatef(i+0.5, j+0.5, k+0.5);
                    
                    // draw the cube
                    glutSolidCube(1);
                    
                    // draw cube souround
                    glBegin(GL_LINES);
                    glLineWidth(5.0f);
                    glColor3f(1.0f, 0.0, 0.0);
                    if ((i-1 > 0 && cubes[i-1][j][k] != 1) && (j-1 > 0 && cubes[i][j-1][k] != 1)) {
                        glVertex3f(-0.5, -0.5, -0.5);
                        glVertex3f(-0.5, -0.5, 0.5);
                    }
                    
                    if ((i+1 < N && cubes[i+1][j][k] != 1) && (j-1 > 0 && cubes[i][j-1][k] != 1)) {
                        glVertex3f(0.5, -0.5, -0.5);
                        glVertex3f(0.5, -0.5, 0.5);
                    }
                    
                    if ((k-1 > 0 && cubes[i][j][k-1] != 1) && (j-1 > 0 && cubes[i][j-1][k] != 1)) {
                        glVertex3f(-0.5, -0.5, -0.5);
                        glVertex3f(0.5, -0.5, -0.5);
                    }
                    
                    if ((k+1 < N && cubes[i][j][k+1] != 1) && (j-1 > 0 && cubes[i][j-1][k] != 1)) {
                        glVertex3f(-0.5, -0.5, 0.5);
                        glVertex3f(0.5, -0.5, 0.5);
                    }
                    
                    if ((i-1 > 0 && cubes[i-1][j][k] != 1) && (j+1 < N && cubes[i][j+1][k] != 1)) {
                        glVertex3f(-0.5, 0.5, -0.5);
                        glVertex3f(-0.5, 0.5, 0.5);
                    }
                    
                    if ((i+1 < N && cubes[i+1][j][k] != 1) && (j+1 < N && cubes[i][j+1][k] != 1)) {
                        glVertex3f(0.5, 0.5, -0.5);
                        glVertex3f(0.5, 0.5, 0.5);
                    }
                    
                    if ((k-1 > 0 && cubes[i][j][k-1] != 1) && (j+1 < N && cubes[i][j+1][k] != 1)) {
                        glVertex3f(-0.5, 0.5, -0.5);
                        glVertex3f(0.5, 0.5, -0.5);
                    }
                    
                    if ((k+1 < N && cubes[i][j][k+1] != 1) && (j+1 < N && cubes[i][j+1][k] != 1)) {
                        glVertex3f(-0.5, 0.5, 0.5);
                        glVertex3f(0.5, 0.5, 0.5);
                    }
                    
                    if ((k-1 > 0 && cubes[i][j][k-1] != 1) && (i-1 > 0 && cubes[i-1][j][k] != 1)) {
                        glVertex3f(-0.5, -0.5, -0.5);
                        glVertex3f(-0.5, 0.5, -0.5);
                    }
                    
                    if ((k+1 < N && cubes[i][j][k+1] != 1) && (i-1 > 0 && cubes[i-1][j][k] != 1)) {
                        glVertex3f(-0.5, -0.5, 0.5);
                        glVertex3f(-0.5, 0.5, 0.5);
                    }
                    
                    if ((k+1 < N && cubes[i][j][k+1] != 1) && (i+1 < N && cubes[i+1][j][k] != 1)) {
                        glVertex3f(0.5, -0.5, 0.5);
                        glVertex3f(0.5, 0.5, 0.5);
                    }

                    if ((k-1 > 0 && cubes[i][j][k-1] != 1) && (i+1 < N && cubes[i+1][j][k] != 1)) {
                        glVertex3f(0.5, -0.5, -0.5);
                        glVertex3f(0.5, 0.5, -0.5);
                    }
                    glLineWidth(1.0f);
                    glEnd();
                    
                    // pop previous matrix
                    glPopMatrix();
                }
            }
        }
    }
}

void handleKeyboard(unsigned char key, int x, int y) {
    
    // zoom out
    if (key == 'q') {
        zoom += 0.01;
    }
    
    // zoom in
    if (key == 'w') {
        zoom -= 0.01;
    }
    
    // rotate camera left
    if (key == 'a') {
        angley--;
    }
    
    // rotate camera right
    if (key == 's') {
        angley++;
    }
    
    // rotate camera up
    if (key == 'z') {
        anglexz--;
    }
    
    // rotate camera down
    if (key == 'x') {
        anglexz++;
    }
    
    // start or pause the game
    if (key == 'p') {
        if (gameStatus == NOTHING) {
            gameStatus = START;
            run(0); // start game loop
        } else if (gameStatus == START) {
            gameStatus = PAUSE;
        } else if (gameStatus == PAUSE) {
            gameStatus = START;
            run(0); // start game loop
        }
    }
    
    // increase game speed by 2
    if (key == 'c') {
        speed *= 2;
    }
    
    // decrease game speed by 2
    if (key == 'v') {
        speed /= 2;
    }
    
    glutPostRedisplay();
}

void handleKeyboardSpecial(int key, int x, int y) {
    // move object left
    if (key == GLUT_KEY_LEFT) {
        moveObjectLeft();
    }
    
    // move object right
    if (key == GLUT_KEY_RIGHT) {
        moveObjectRight();
    }
    
    // move object back
    if (key == GLUT_KEY_UP) {
        moveObjectBack();
    }
    
    // move object forward
    if (key == GLUT_KEY_DOWN) {
        moveObjectForward();
    }
    
    glutPostRedisplay();
}

// this function run a game loop
void run(int var) {
    switch (gameStatus) {
        case START:
            glutTimerFunc(speed, run, 0);
            
            // move object down
            moveObjectDown();
            
            break;
        case PAUSE:
            break;
        case NOTHING:
            break;
        case END:
            return;
    }
    glutPostRedisplay();
}

// will move object down
void moveObjectDown() {
    bool move = true;
    for (int i=0; i<4; i++) {
        if (object->cubes[i] != NULL) {
            GLint x = object->cubes[i]->x;
            GLint y = object->cubes[i]->y;
            GLint z = object->cubes[i]->z;
            if (y - 1 < 0 || cubes[x][y-1][z] != 0) {
                
                // game over situation
                if (y == N - 1) {
                    gameStatus = END;
                    return;
                }
                
                move = false;
                break;
            }
        }
    }
    
    if (move) {
        for (int i=0; i<4; i++) {
            if (object->cubes[i] != NULL) {
                object->cubes[i]->y--;
            }
        }
    } else {
        for (int i=0; i<4; i++) {
            if (object->cubes[i] != NULL) {
                GLint x = object->cubes[i]->x;
                GLint y = object->cubes[i]->y;
                GLint z = object->cubes[i]->z;
                cubes[x][y][z] = 1;                // otan ftasei to object katw kai enopoieithei me ta ipoloipa kivakia tote svinw tis grammes
            }
        }
        
        // calculate points
        points += 10 * object->cubesNumber;
        
        // remove objects MxMxM with M >= 4
        findLargeObject(0, 0, 0, M);
        if (objectFound) {
            for (int i=x; i<x+scaleFound; i++) {
                for (int j=y; j<y+scaleFound; j++) {
                    for (int k=z; k<z+scaleFound; k++) {
                        cubes[i][j][k] = 0;
                    }
                }
            }
            points += powl(scaleFound, 3);
            objectFound = false;
        }
        
        // create a new object to fall
        object->createObject(N);
        
    }
}

// will move object left
void moveObjectLeft() {
    bool move = true;
    for (int i=0; i<4; i++) {
        if (object->cubes[i] != NULL) {
            GLint x = object->cubes[i]->x;
            GLint y = object->cubes[i]->y;
            GLint z = object->cubes[i]->z;
            if (x - 1 < 0 || cubes[x-1][y][z] != 0) {
                move = false;
                break;
            }
        }
    }
    
    if (move) {
        for (int i=0; i<4; i++) {
            if (object->cubes[i] != NULL) {
                object->cubes[i]->x--;
            }
        }
    }
}

// will move object right
void moveObjectRight() {
    bool move = true;
    for (int i=0; i<4; i++) {
        if (object->cubes[i] != NULL) {
            GLint x = object->cubes[i]->x;
            GLint y = object->cubes[i]->y;
            GLint z = object->cubes[i]->z;
            if (x + 1 >= N || cubes[x+1][y][z] != 0) {
                move = false;
                break;
            }
        }
    }
    
    if (move) {
        for (int i=0; i<4; i++) {
            if (object->cubes[i] != NULL) {
                object->cubes[i]->x++;
            }
        }
    }
}

// will move object back
void moveObjectBack() {
    bool move = true;
    for (int i=0; i<4; i++) {
        if (object->cubes[i] != NULL) {
            GLint x = object->cubes[i]->x;
            GLint y = object->cubes[i]->y;
            GLint z = object->cubes[i]->z;
            if (z - 1 < 0 || cubes[x][y][z-1] != 0) {
                move = false;
                break;
            }
        }
    }
    
    if (move) {
        for (int i=0; i<4; i++) {
            if (object->cubes[i] != NULL) {
                object->cubes[i]->z--;
            }
        }
    }
}

// will move object forward
void moveObjectForward() {
    bool move = true;
    for (int i=0; i<4; i++) {
        if (object->cubes[i] != NULL) {
            GLint x = object->cubes[i]->x;
            GLint y = object->cubes[i]->y;
            GLint z = object->cubes[i]->z;
            if (z + 1 >= N || cubes[x][y][z+1] != 0) {
                move = false;
                break;
            }
        }
    }
    
    if (move) {
        for (int i=0; i<4; i++) {
            if (object->cubes[i] != NULL) {
                object->cubes[i]->z++;
            }
        }
    }
}

// check specific array in the cubes
// if one with MxMxM is found return true
bool checkArrayOfCubes(GLint x, GLint y, GLint z, GLint scale) {
    for (int i=x; i<x+scale; i++) {
        for (int j=y; j<y+scale; j++) {
            for (int k=z; k<z+scale; k++) {
                if (cubes[i][j][k] != 1) {
                    return false;
                }
            }
        }
    }
    return true;
}

// find large object in the cubes 3-dimension array
void findLargeObject(GLint i1, GLint j1, GLint k1, GLint scale) {
    for (int i=i1; i<N-scale; i++) {
        for (int j=j1; j<N-scale; j++) {
            for (int k=k1; k<N-scale; k++) {
                if (checkArrayOfCubes(i, j, k, scale)) {
                    objectFound = true;
                    x = i;
                    y = j;
                    z = k;
                    scaleFound = scale;
                    
                    findLargeObject(i, j, k, scale+1);
                }
            }
        }
    }
}

// print user points on top left of the window
void printPoints() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    stringstream s;
    
    if (gameStatus == END) {
        s << "Game Over - ";
    }
    s << points;
    char message[20] = "";
    char * final_message = strcat(message,s.str().c_str());
    glColor3f(0.2, 0.5, 0.7);
    glRasterPos2d(10, 480);
    for (int i=0; i<strlen(final_message); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, final_message[i]);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}
