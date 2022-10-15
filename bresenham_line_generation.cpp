// Line generation using Bresenham's Line Generation Algorithm.
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;
int X0, X1, Y0, Y1;

void display() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int dx, dy, x, y, p, x_inc, y_inc;

    dx = abs(X1 - X0);
    dy = abs(Y1 - Y0);

    if(X0 > X1)
        x_inc = -1;
    else
        x_inc = 1;

    if(Y0 > Y1)
        y_inc = -1;
    else
        y_inc = 1;

    x = X0;
    y = Y0;

    if(dx > dy) {
        p = 2*dy - dx;

        glBegin(GL_POINTS);
            glVertex2f(x, y);
            for(int k=0; k < dx; k++)
            {
                if(p < 0)
                    p = p + 2*dy;
                else {
                    p = p + 2*dy - 2*dx;
                    y = y + y_inc;
                }

                x = x + x_inc;
                glVertex2f(x, y);
            }
        glEnd();
    }

    else {
        p = 2*dx - dy;

        glBegin(GL_POINTS);
            glVertex2f(x, y);
            for(int k=0; k < dx; k++)
            {
                if(p < 0)
                    p = p + 2*dx;
                else {
                    p = p + 2*dx - 2*dy;
                    x = x + x_inc;
                }

                y = y + y_inc;
                glVertex2f(x, y);
            }
        glEnd();
    }
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
    glutCreateWindow("Line Generation using Bresenham's Algorithm");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
