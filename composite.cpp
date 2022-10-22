#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

int choice;
float P_old[3][3], P_new[3][3], T[3][3], T1[3][3], T2[3][3], S[3][3], Rt[3][3], Rf[3][3];
float m, c, phi;
float h, k, theta, sx, sy;

void matrixMult(float A[3][3], float B[3][3], float C[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            C[j][i] = A[j][0] * B[0][i] + A[j][1] * B[1][i] + A[j][2] * B[2][i];
}

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++)
        glVertex2f(P_old[0][i], P_old[1][i]);
    glEnd();

    matrixMult(T, P_old, P_new);

    if (choice == 1)
    {
        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(0, c);
        glVertex2f(600, m * 600 + c);
        glEnd();
    }

    if (choice == 2)
    {
        glColor3f(1.0f, 1.0f, 0.0f);
        glPointSize(5);
        glBegin(GL_POINTS);
        glVertex2f(h, k);
        glEnd();
    }

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++)
        glVertex2f(P_new[0][i], P_new[1][i]);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    P_old[0][0] = 300;
    P_old[1][0] = 100;
    P_old[2][0] = 1;
    P_old[0][1] = 400;
    P_old[1][1] = 250;
    P_old[2][1] = 1;
    P_old[0][2] = 500;
    P_old[1][2] = 100;
    P_old[2][2] = 1;
    //    cout<<"Enter the coordinates of the vertices:\n";
    //    for(int i=0; i<3; i++) {
    //        cin>>P_old[0][i];   // x coordinate
    //        cin>>P_old[1][i];   // y cooridnate
    //        P_old[2][i] = 1;
    //    }

    cout << "Composite Transformation: \n";
    cout << "1. Reflection about a line y = mx + c\n";
    cout << "2. Rotation and Scaling about a fixed point\n\n";
    cout << "Enter transformation choice: ";
    cin >> choice;

    if (choice == 1)
    {
        m = 0.5;
        c = 100;
        //        cout<<"Enter the slope (m) and y-intercept (c) of line: ";
        //        cin>>m>>c;

        phi = 2 * tanh(m);

        T1[0][0] = 1;
        T1[0][1] = 0;
        T1[0][2] = 0;
        T1[1][0] = 0;
        T1[1][1] = 1;
        T1[1][2] = -c;
        T1[2][0] = 0;
        T1[2][1] = 0;
        T1[2][2] = 1;

        Rf[0][0] = 1;
        Rf[0][1] = 0;
        Rf[0][2] = 0;
        Rf[1][0] = 0;
        Rf[1][1] = -1;
        Rf[1][2] = 0;
        Rf[2][0] = 0;
        Rf[2][1] = 0;
        Rf[2][2] = 1;

        Rt[0][0] = cos(phi);
        Rt[0][1] = -sin(phi);
        Rt[0][2] = 0;
        Rt[1][0] = sin(phi);
        Rt[1][1] = cos(phi);
        Rt[1][2] = 0;
        Rt[2][0] = 0;
        Rt[2][1] = 0;
        Rt[2][2] = 1;

        T2[0][0] = 1;
        T2[0][1] = 0;
        T2[0][2] = 0;
        T2[1][0] = 0;
        T2[1][1] = 1;
        T2[1][2] = c;
        T2[2][0] = 0;
        T2[2][1] = 0;
        T2[2][2] = 1;

        T[0][0] = 1;
        T[0][1] = 0;
        T[0][2] = 0;
        T[1][0] = 0;
        T[1][1] = 1;
        T[1][2] = 0;
        T[2][0] = 0;
        T[2][1] = 0;
        T[2][2] = 1;

        float temp1[3][3], temp2[3][3];
        matrixMult(T2, Rt, temp1);
        matrixMult(temp1, Rf, temp2);
        matrixMult(temp2, T1, T);

        //        T[0][0] = cos(phi); T[0][1] = sin(phi); T[0][2] = -c * cos(phi);
        //        T[1][0] = sin(phi); T[1][1] = -cos(phi); T[1][2] = c * cos(phi) + c;
        //        T[2][0] = 0; T[2][1] = 0; T[2][2] = 1;
    }

    else if (choice == 2)
    {
        h = 100, k = 100;
        theta = 30;
        sx = 0.5;
        sy = 0.5;

        //        cout<<"Enter the coordinates of fixed point: ";
        //        cin>>h>>k;
        //        cout<<"Enter the rotation angle: ";
        //        cin>>theta;
        //        cout<<"Enter the scaling factor: ";
        //        cin>>sx>>sy;

        theta = theta * (3.14159265359 / 180.0);

        T1[0][0] = 1;
        T1[0][1] = 0;
        T1[0][2] = -h;
        T1[1][0] = 0;
        T1[1][1] = 1;
        T1[1][2] = -k;
        T1[2][0] = 0;
        T1[2][1] = 0;
        T1[2][2] = 1;

        Rt[0][0] = cos(theta);
        Rt[0][1] = -sin(theta);
        Rt[0][2] = 0;
        Rt[1][0] = sin(theta);
        Rt[1][1] = cos(theta);
        Rt[1][2] = 0;
        Rt[2][0] = 0;
        Rt[2][1] = 0;
        Rt[2][2] = 1;

        S[0][0] = sx;
        S[0][1] = 0;
        S[0][2] = 0;
        S[1][0] = 0;
        S[1][1] = sy;
        S[1][2] = 0;
        S[2][0] = 0;
        S[2][1] = 0;
        S[2][2] = 1;

        T2[0][0] = 1;
        T2[0][1] = 0;
        T2[0][2] = h;
        T2[1][0] = 0;
        T2[1][1] = 1;
        T2[1][2] = k;
        T2[2][0] = 0;
        T2[2][1] = 0;
        T2[2][2] = 1;

        float temp1[3][3], temp2[3][3];
        matrixMult(T2, S, temp1);
        matrixMult(temp1, Rt, temp2);
        matrixMult(temp2, T1, T);

        //        T[0][0] = sx * cos(theta); T[0][1] = -sx * sin(theta); T[0][2] = -h * sx * cos(theta) + k * sx * sin(theta) + h;
        //        T[1][0] = sy * sin(theta); T[1][1] = sy * cos(theta); T[1][2] = -h * sy * sin(theta) - k * sy * cos(theta) + k;
        //        T[2][0] = 0; T[2][1] = 0; T[2][2] = 1;
    }

    else
    {
        cout << "INVALID CHOICE\n";
        return -1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Composite Transformations");
    gluOrtho2D(0, 600, 0, 600);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}