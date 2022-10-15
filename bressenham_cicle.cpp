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
    x=0,y=R;
    float D=3-2*R;

    while(x<=y){
        plot(x,y);
        if(D<0)
            D+=4*x+6;
        else{
            D+=4*(x-y)+10;
            y--;
        }
        x++;
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
    glutCreateWindow("Circle Generation using Bresenham's Algo");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
