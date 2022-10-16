//Line generation using digital differential analyser DDA algorithm.
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;
float X0, X1, Y0, Y1;

void display() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float dx, dy, step, x, y, x_inc, y_inc;

    dx = X1 - X0;
    dy = Y1 - Y0;

    if(abs(dx)> abs(dy))
        step = abs(dx);
    else
        step = abs(dy);

    x_inc = dx / step;
    y_inc = dy / step;

    x = X0;
    y = Y0;

    glBegin(GL_POINTS);
        glVertex2f(x, y);
        for(int k=1; k<=step; k++)
        {
            x = x + x_inc;
            y = y + y_inc;
            glVertex2f(x, y);
        }
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    cout<<"Enter the value of X0 : ";
    cin>>X0;
    cout<<"Enter the value of Y0 : ";
    cin>>Y0;
    cout<<"Enter the value of X1 : ";
    cin>>X1;
    cout<<"Enter the value of Y1 : ";
    cin>>Y1;

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Line Generation using DDA");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
