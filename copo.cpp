#include <iostream>
#include <cmath>
#include <GL/glut.h>

const double PI = 3.14159;
const int p = 50;
const int q = 50;

float f(int i, int j)
{
    return (cos((-1 + 2 * (float)i / p) * PI));
}

float g(int i, int j)
{
    return (sin((-1 + 2 * (float)i / p) * PI));
}

float h(int i, int j)
{
    return (-1 + 2 * (float)j / q);
}

void drawCup(double raioBase, double raioTopo, double altura)
{
    double deltaTheta = 2 * PI / p;
    double deltaZ = altura / (q - 1);

    for (int i = 0; i < p; i++)
    {
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= q; j++)
        {
            double theta = i * deltaTheta;
            double z = j * deltaZ;

            double xBase = raioBase * f(i, j);
            double yBase = raioBase * g(i, j);

            double xTopo = raioTopo * f(i, j);
            double yTopo = raioTopo * g(i, j);

            double nx = f(i, j);
            double ny = g(i, j);
            double nz = h(i, j);

            // Desenha a base do copo
            glNormal3d(0, 0, -1);
            glVertex3d(xBase, yBase, 0);

            // Desenha a superfície lateral do copo
            glNormal3d(nx, ny, nz);
            glVertex3d(xTopo, yTopo, z);
        }
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    glColor3f(0.5, 0.5, 0.5);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[4] = {0.0, 10.0, 10.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glRotatef(30, 1, 0, 0);
    glRotatef(30, 0, 1, 0);

    drawCup(1.0, 0.5, 2.0); // Raio da base, raio do topo e altura do copo

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)width / height, 1, 10);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cup");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();


    return 0;
}

