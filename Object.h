#ifndef __PLY701_1__Object__
#define __PLY701_1__Object__

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h> 
#include "Cube.h"

using namespace std;

class Object {
public:
    Cube *cubes[4];
    GLint cubesNumber;
    Object() {
        for (int i=0; i<4; i++) {
            cubes[i] = NULL;
        }
    }
    void createObject(GLint);
    void createCubes();
};

#endif
