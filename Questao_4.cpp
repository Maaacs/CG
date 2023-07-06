#include <GL/glut.h>

float bezierCurve(float t, float p0, float p1, float p2, float p3) {
    float u = 1.0 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    float result = uuu * p0;
    result += 3 * uu * t * p1;
    result += 3 * u * tt * p2;
    result += ttt * p3;

    return result;
}

void drawBezierSurface() {
    int numSegments = 100;
    int numSlices = 20;

    for (int i = 0; i < numSlices; i++) {
        float t1 = (float)i / (float)numSlices;
        float t2 = (float)(i + 1) / (float)numSlices;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= numSegments; j++) {
            float t = (float)j / (float)numSegments;

            float x = bezierCurve(t, 1, 3, 2, 5);
            float y = bezierCurve(t, 0, 0, 0, 0);
            float z = bezierCurve(t, 2, 4, 6, 7);

            glVertex3f(x * cos(t1 * 2 * M_PI), y, x * sin(t1 * 2 * M_PI));
            glVertex3f(x * cos(t2 * 2 * M_PI), y, x * sin(t2 * 2 * M_PI));
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 10, 10, 0, 0, 0, 0, 1, 0);

    drawBezierSurface();

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Superfície de Rotação com Curva de Bezier");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
