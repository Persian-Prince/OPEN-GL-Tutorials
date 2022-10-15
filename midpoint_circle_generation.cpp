#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>

float x,y,R;
float xc,yc;

void show_pixels(float x, float y)
{
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void plot(float x,float y){
    show_pixels(x+xc,y+yc);
    show_pixels(-x+xc,y+yc);
    show_pixels(x+xc,-y+yc);
    show_pixels(-x+xc,-y+yc);
    show_pixels(-y+xc,-x+yc);
    show_pixels(-y+xc,x+yc);
    show_pixels(y+xc,-x+yc);
    show_pixels(y+xc,x+yc);
}

void display(void)
{
    x=0,y=R;
    float P=1-R;

    while(x<=y){
        plot(x,y);
        if(P<0)
            P+=2*x+3;
        else{
            P+=2*(x-y)+5;
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
    xc=0,yc=0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle Generation using Mid point method");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
