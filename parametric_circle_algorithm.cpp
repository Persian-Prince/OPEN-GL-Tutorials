// Program to draw a circle using parametric algorithm.
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;
int a, b, h, k;

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int x, y, theta, step;

    theta = 0;
    step = 1;

    glBegin(GL_POINTS);
        while(theta <= 360) {
            x = h + a * cos(theta);
            y = k + b * sin(theta);
            glVertex2f(x, y);
            theta += step;
        }
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    cout<<"Enter the value of a : ";
    cin>>a;
    cout<<"Enter the value of b : ";
    cin>>b;
    cout<<"Enter the value of h : ";
    cin>>h;
    cout<<"Enter the value of k : ";
    cin>>k;

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle and Ellipse Generation using Parametric Equation");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
    return 0;
}
