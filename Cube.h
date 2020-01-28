#ifndef __PLY701_1__Cube__
#define __PLY701_1__Cube__

#include <iostream>
#include <GL/glut.h> 

using namespace std;

class Cube {

public:
    Cube () {
        x = -1;     //initialize cube to put it out of the grid
        y = -1;
        z = -1;
    }
    Cube (GLint x, GLint y, GLint z) : x(x), y(y), z(z) {}
    GLint x; // location on x
    GLint y; // location on y
    GLint z; // location on z
    void create(GLint leftx, GLint rightx, GLint lefty, GLint righty, GLint leftz, GLint rightz);
};

#endif
