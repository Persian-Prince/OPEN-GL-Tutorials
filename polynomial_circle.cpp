// Program to draw a circle using polynomial algorithm.
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>

float x,y,R;

void show_pixels(float x, float y)
{
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void plot(float x,float y){
    show_pixels(x,y);
    show_pixels(-x,y);
    show_pixels(x,-y);
    show_pixels(-x,-y);
    show_pixels(-y,-x);
    show_pixels(-y,x);
    show_pixels(y,-x);
    show_pixels(y,x);
}

void display(void)
{

    for(x =0;x<=(R*(sqrt(2)))/2;x+=1)
    {
        y= sqrt(R*R - x*x);
        plot(x,y);
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
    printf("Enter Radius : ");
    scanf("%f",&R);
    // R= 80;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle Generation using Polynomial method");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

