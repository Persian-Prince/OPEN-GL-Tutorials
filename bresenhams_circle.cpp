// Circle generation using Bresenham's circle generation algorithm.
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;
int r, h, k;

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int x, y, d, x_inc, y_inc;

    x = 0;
    y = r;
    d = 3 - 2*r;
    x_inc = 1;
    y_inc = -1;

    glBegin(GL_POINTS);
        while(x < y) {
            glVertex2i(h + x, k + y);
            glVertex2i(h + x, k - y);
            glVertex2i(h - x, k + y);
            glVertex2i(h - x, k - y);
            glVertex2i(h + y, k + x);
            glVertex2i(h + y, k - x);
            glVertex2i(h - y, k + x);
            glVertex2i(h - y, k - x);

            if(d < 0)
                d = d + 4*x + 6;
            else {
                d = d + 4*(x-y) + 10;
                y = y + y_inc;
            }

            x = x + x_inc;
        }
    glEnd();
    glFlush();
}
int main(int argc, char** argv)
{
    cout<<"Enter the value of r : ";
    cin>>r;
    cout<<"Enter the value of h : ";
    cin>>h;
    cout<<"Enter the value of k : ";
    cin>>k;

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle Generation using Bresenham's Algorithm");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
