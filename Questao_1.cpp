#include <GL/glut.h>
#include <math.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    GLfloat Ax = 1.0f, Ay = 0.0f, Az = 1.0f;
    GLfloat Bx = 7.0f, By = 0.0f, Bz = 7.0f;
    GLfloat angle = 0.0f;

    int numSegments = 100;

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numSegments; ++i) {
        
        angle = (GLfloat)i / numSegments * 2.0f * M_PI;

        GLfloat Cx = cos(angle) * Bx - sin(angle) * By;
        GLfloat Cy = sin(angle) * Bx + cos(angle) * By;
        GLfloat Cz = Bz;
        glVertex3f(Ax, Ay, Az);
        glVertex3f(Bx, By, Bz);
        glVertex3f(Cx, Cy, Cz);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Superfície Cônica");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.33, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}