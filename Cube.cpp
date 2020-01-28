#include "Cube.h"

void Cube::create(GLint leftx, GLint rightx, GLint lefty, GLint righty, GLint leftz, GLint rightz) {
    glColor3f(0.1, 0.5, 0.9);  //blue
    
    // push current matrix
    glPushMatrix();
    
    // translate location
    glTranslatef(x+0.5, y+0.5, z+0.5);
    
    // draw the cube
    glutSolidCube(1);            // to orisma einai to mikos tis akmis tou kivou
    
    // draw cube souround
    glBegin(GL_LINES);
    glLineWidth(5.0f);
    glColor3f(1.0f, 0.0, 0.0);        //red color
    if (leftx == 0 && lefty == 0) {
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);                    // sxediasi 12 akmwn tou kivou
    }
    
    if (rightx == 0 && lefty == 0) {
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, 0.5);
    }
    
    if (leftz == 0 && lefty == 0) {
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
    }
    
    if (rightz == 0 && lefty == 0) {
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
    }
    
    if (leftx == 0 && righty == 0) {
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
    }
    
    if (rightx == 0 && righty == 0) {
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
    }
    
    if (leftz == 0 && righty == 0) {
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
    }
    
    if (rightz == 0 && righty == 0) {
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
    }
    
    if (leftz == 0 && leftx == 0) {
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
    }
    
    if (rightz == 0 && leftx == 0) {
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
    }
    
    if (rightz == 0 && rightx == 0) {
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
    }
    
    if (leftz == 0 && rightx == 0) {
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
    }
    glLineWidth(1.0f);
    glEnd();
    
    // pop previous matrix
    glPopMatrix();
}
