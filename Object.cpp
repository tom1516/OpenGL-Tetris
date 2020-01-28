#include "Object.h"

// create a new object
void Object::createObject(GLint N) {
    for (int i=0; i<4; i++) {
        cubes[i] = NULL;         
    }
    
    // where object start is shown in the grid
    GLint location = N / 2;      //kentro skinis
    
    cubesNumber = rand() % 4 + 1;   //gia na min rinai pote 0 o arithmos ton kivwn pou peftoun
//    cubesNumber = 1;
    cubes[0] = new Cube(location, N-1, location);        // neos kivos sto location  N-1
    
    bool cubeFound = false;
    
    for (int i=1; i<cubesNumber; i++) {
        GLint x1 = cubes[i-1]->x;
        GLint y1 = cubes[i-1]->y;
        GLint z1 = cubes[i-1]->z;
        
        GLint d = rand() % 5 + 1;           //gia na dw pou tha prosthesw kai allon kivo
        if (d == 0) { // increase on x
            x1++;
        } else if (d == 1) { // decrease on x
            x1--;
        } else if (d == 2) { // increase on z
            z1++;
        } else if (d == 3) { // decrease on z
            z1--;
        } else if (d == 4) { // increase on y
            y1++;
        } else if (d == 5) { // decrease on y
            y1--;
        }
        
        for (int j=0; j<i; j++) {
            if (cubes[j]->x == x1 && cubes[j]->y == y1 && cubes[j]->z == z1) {
                cubeFound = true;                                                   //ελεγχω αν εχω ειδη τοποθετήσει καποιον αλλον κυβο 
            }                                                                       //δεξια αριστερα η πάνω κάτω. αν ναι τότε cubrfound=true;
        }                                                                           // και μειώνω to i και ξαναρχίζω πάλι απο το for!!!
        
        if (cubeFound) {
            i--;
            cubeFound = false;
            continue;
        }
        
        cubes[i] = new Cube(x1, y1, z1);                                            //δημιουργώ ένανα νέο κύβο
    }
}

// draw all cubes of the object in the grid
void Object::createCubes() {
    for (int i=0; i<cubesNumber; i++) {
        GLint leftx = 0;
        GLint rightx = 0;
        GLint lefty = 0;
        GLint righty = 0;
        GLint leftz = 0;
        GLint rightz = 0;
        
        GLint x = cubes[i]->x;
        GLint y = cubes[i]->y;
        GLint z = cubes[i]->z;
        
        for (int j=0; j<cubesNumber; j++) {
            if (j == i) {
                continue;
            }
            
            GLint x1 = cubes[j]->x;
            GLint y1 = cubes[j]->y;
            GLint z1 = cubes[j]->z;
            
            if (x - 1 == x1 && y == y1 && z == z1) {
                leftx = 1;
            }
            
            if (x + 1 == x1 && y == y1 && z == z1) {
                rightx = 1;
            }
            
            if (y - 1 == y1 && x == x1 && z == z1) {
                lefty = 1;
            }
            
            if (y + 1 == y1 && x == x1 && z == z1) {
                righty = 1;
            }
            
            if (z - 1 == z1 && y == y1 && x == x1) {
                leftz = 1;
            }
            
            if (z + 1 == z1 && y == y1 && x == x1) {
                rightz = 1;
            }
        }

        cubes[i]->create( leftx,  rightx,  lefty,  righty,  leftz, rightz);
    }
}
