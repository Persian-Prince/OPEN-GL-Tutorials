// Program to draw a circle using polynomial algorithm.
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

int h,k,r;
void display(void)
 {
 double XEnd,J;
 int i,j;
 glClear (GL_COLOR_BUFFER_BIT);
 glColor3f (1.0, 0.0, 0.0);
 XEnd=(r/1.414);
 glBegin(GL_POINTS);
 glVertex2s(h,k);
 for( i=0 ; i<=XEnd ; i++)
 { 
 J=sqrt(r*r - i*i);
 j=(int)(J);
 glVertex2s(h+i,k+j);
 glVertex2s(h+j,k+i);
 glVertex2s(h-i,k+j);
 glVertex2s(h-j,k+i);
 glVertex2s(h-j,k-i);
 glVertex2s(h-i,k-j);
 glVertex2s(h+i,k-j);
 glVertex2s(h+j,k-i);
 }
 glColor3f (1.0, 1.0, 1.0);
 for(int i=-100 ; i<=100 ; i++)
 {
 glVertex2s(i,0);
 glVertex2s(0,i);
 }
 for(int i=-2; i<=2 ; i++)
 {
 glVertex2s(95+i,4+i);
 glVertex2s(95-i,4+i);
 } 
 for(int i=0; i<=2 ; i++)
 {
 glVertex2s(4+i,95+i);
 glVertex2s(4-i,95+i);
 glVertex2s(4,95-i);
 }
 glEnd();
 glFlush();
 }
void init(void)
 {
 glClearColor (0.0, 0.0, 0.0, 0.0);
 glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
 }
int main(int argc, char** argv)
{
 printf("Enter the center of circle:\n");
 scanf("%d %d",&h,&k);
 printf("Enter the radius:\n");
 scanf("%d",&r);
 glutInit(&argc, argv);
 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize (500, 500);
 glutInitWindowPosition (100, 100);
 glutCreateWindow ("Circle : Polynomial Method ");
 init ();
 glutDisplayFunc(display);
 glutMainLoop();
 return 0;
}
