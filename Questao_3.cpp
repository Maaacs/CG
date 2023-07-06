#include <GL/glut.h>
#include <cmath>

const int numSlices = 50; // Número de divisões ao longo do círculo principal
const int numStacks = 50; // Número de divisões ao longo do círculo secundário

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -30.0f); // Translação para que o torus fique visível na tela

    glColor3f(0.5f, 0.5f, 1.0f); // Cor do torus

    // Desenhar o torus
    for (int i = 0; i < numSlices; ++i) {
        float theta1 = i * 2.0f * M_PI / numSlices;
        float theta2 = (i + 1) * 2.0f * M_PI / numSlices;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= numStacks; ++j) {
            float phi = j * 2.0f * M_PI / numStacks;

            // Coordenadas dos vértices
            float x1 = (10 + 3 * cos(phi)) * cos(theta1);
            float y1 = (10 + 3 * cos(phi)) * sin(theta1);
            float z1 = 3 * sin(phi);

            float x2 = (10 + 3 * cos(phi)) * cos(theta2);
            float y2 = (10 + 3 * cos(phi)) * sin(theta2);
            float z2 = 3 * sin(phi);

            // Desenhar os vértices
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / height, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Torus");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
