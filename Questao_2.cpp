#include <GL/glut.h>
#include <cmath>

float rotateX = 0.0f;
float rotateY = 0.0f;

void drawDisk(float radius, int numSlices) {
    glBegin(GL_TRIANGLE_FAN);

    // Centro do disco
    glVertex3f(5.0f, 0.0f, 10.0f);

    // Pontos ao longo da circunferência do disco
    for (int i = 0; i <= numSlices; i++) {
        float theta = ((float)i / numSlices) * 2 * M_PI;
        float x = 5.0f + radius * cos(theta);
        float y = 0.0f;
        float z = 10.0f + radius * sin(theta);

        glVertex3f(x, y, z);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 10, 20, 0, 0, 0, 0, 1, 0);

    glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Rotação em torno do eixo X
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Rotação em torno do eixo Y

    glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha

    drawDisk(5.0f, 100);

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'q') {
        rotateX += 5.0f;
    } else if (key == 'e') {
        rotateX -= 5.0f;
    } else if (key == 'a') {
        rotateY += 5.0f;
    } else if (key == 'd') {
        rotateY -= 5.0f;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Disco em OpenGL");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
