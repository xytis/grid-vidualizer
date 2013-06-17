#include <iostream>
#include <cstdlib>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "CGrid.h"

#include <cmath>
#include <vector>
using namespace std;

float _angle;

CGrid * _grid;

void handleKeypress(unsigned char key, int x, int y) {
        switch (key) {
                case 27: //Escape key
                        exit(0);
                
        }
}

void handleMouse(int button, int state, int x, int y) {

}

void initRendering() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glShadeModel(GL_SMOOTH);
}

void handleResize(int w, int h) {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void drawScene() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -10.0f);
        glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(-_angle, 0.0f, 0.0f, 1.0f);
        
        GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
        
        GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
        GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
        
        _grid->draw();        
        
        glutSwapBuffers();
}

void update(int value) {
        _angle += 0.1f;
        if (_angle > 360) {
                _angle -= 360;
        }
        
        glutPostRedisplay();
        glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(800, 800);
        
        glutCreateWindow("Grid path");
        initRendering();
    
        _grid = new CGrid(16,16);
        
        glutDisplayFunc(drawScene);
        glutKeyboardFunc(handleKeypress);
        glutMouseFunc(handleMouse);
        glutReshapeFunc(handleResize);
        glutTimerFunc(25, update, 0);
        
        glutMainLoop();
        return 0;
}









