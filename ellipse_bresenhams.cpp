// Program to draw ellipse using Bresenham's Ellipse Generation Algorithm.
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float x, y, a, b;
float h, k;
int aa, bb;
int d;

void show_pixels(float x, float y)
{
    glPointSize(1);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void plot(float x, float y)
{
    show_pixels(x + h, y + k);
    show_pixels(-x + h, y + k);
    show_pixels(x + h, -y + k);
    show_pixels(-x + h, -y + k);
}

void display(void)
{
    x = 0, y = b;
    aa = a * a, bb = b * b;
    d = 2 * bb + aa - 2 * b * aa;

    while (bb * x < aa * y)
    {
        plot(x, y);
        if (d < 0)
            d += (2 * bb) * (2 * x + 3);
        else
        {
            d += (2 * bb) * (2 * x + 3) + (4 * aa) * (1 - y);
            y--;
        }
        x++;
    }
    plot(x, y);
    d = 2 * aa * (y - 1) * (y - 1) + bb * (2 * x * x + 2 * x + 1) - 2 * aa * bb;
    while (y != 0)
    {
        if (d >= 0)
            d += 2 * aa * (3 - 2 * y);
        else
        {
            d += 2 * aa * (3 - 2 * y) + 4 * bb * (1 + x);
            x++;
        }
        y--;
        plot(x, y);
    }

    glFlush();
}

void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    printf("Enter a : ");
    scanf("%f",&a);
    printf("Enter b : ");
    scanf("%f",&b);
    // a = 80, b = 60;
    h = 250, k = 250;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ellipe Generation using Bresenham's Algo");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
