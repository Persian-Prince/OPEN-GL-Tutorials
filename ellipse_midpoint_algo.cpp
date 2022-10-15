// Program to draw an ellipse using mid point algorithm.
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float x, y, a, b;
float h, k;
int aa, bb;
int p;

void show_pixels(float x, float y)
{
    glPointSize(4);
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
    p = bb + aa / 4 - b * aa;

    while (bb * x < aa * y)
    {
        plot(x, y);
        x++;
        if (p < 0)
            p += bb * 2 * x + bb;
        else
        {
            y--;
            p += 2 * x * bb + bb - 2 * y * aa;
        }
    }
    plot(x, y);
    p = bb * (x + 1 / 2) * (x + 1 / 2) + aa * (y - 1) * (y - 1) - aa * bb;
    while (y != 0)
    {
        y--;
        if (p > 0)
            p += aa - (aa * 2 * y);
        else
        {
            x++;
            p += bb * 2 * x - 2 * y * aa + aa;
        }
        plot(x, y);
    }

    glFlush();
}

void init(void)
{
    glClearColor(0.5, 0.5, 0.0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char **argv)
{
    printf("Enter a : ");
    scanf("%f",&a);
    printf("Enter b : ");
    scanf("%f",&b);
    // a = 80, b = 40;
    h = 0, k = 0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ellipse Generation Algo using mid point method");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
