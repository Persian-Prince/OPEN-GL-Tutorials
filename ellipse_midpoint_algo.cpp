// Program to draw an ellipse using mid point algorithm.
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;
int a, b, h, k;

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float x, y, x_inc, y_inc, d, dx, dy, rx, ry, rx2, ry2;

    rx = a*a;
    ry = b*b;
    rx2 = 2*rx;
    ry2 = 2*ry;

    x = 0;
    y = b;

    x_inc = 1;
    y_inc = -1;

    dx = ry2 * x;
    dy = rx2 * y;

    glBegin(GL_POINTS);
        d= ry - (rx * b) + (0.25 * rx);
        do {
            glVertex2i(h + x, k + y);
            glVertex2i(h + x, k - y);
            glVertex2i(h - x, k + y);
            glVertex2i(h - x, k - y);

            if(d < 0) {
                x = x + x_inc;
                dx = dx + ry2;
                d = d + dx + ry;
            }

            else {
                x = x + x_inc;
                y = y + y_inc;
                dx = dx + ry2;
                dy = dy - rx2;
                d = d + dx - dy + ry;
            }

        } while(dx < dy);

        d = ry*(x + 0.5)* (x + 0.5) + rx*(y - 1)*(y - 1) - rx*ry;
        do {
            glVertex2i(h + x, k + y);
            glVertex2i(h + x, k - y);
            glVertex2i(h - x, k + y);
            glVertex2i(h - x, k - y);

            if(d > 0) {
                y = y + y_inc;
                dy = dy - rx2;
                d = d - dy + rx;
            }

            else {
                x = x + x_inc;
                y = y + y_inc;
                dx = dx + ry2;
                dy = dy - rx2;
                d = d + dx - dy + rx;
            }

        }while(y >= 0);
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
    glutCreateWindow("Ellipse Generation using Mid-Point Algorithm");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
