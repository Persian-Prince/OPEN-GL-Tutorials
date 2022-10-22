#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

int V = 0, C = 0;
float P_old[3][100], P_new[3][100], T[3][3];

void matrixMult(float A[3][3], float B[3][100], float C[3][100])
{
    for (int i = 0; i < V; i++)
        for (int j = 0; j < 3; j++)
            C[j][i] = A[j][0] * B[0][i] + A[j][1] * B[1][i] + A[j][2] * B[2][i];
}

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-200, 0);
    glVertex2f(600, 0);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0, -400);
    glVertex2f(0, 400);
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < V; i++)
        glVertex2f(P_old[0][i], P_old[1][i]);
    glEnd();

    matrixMult(T, P_old, P_new);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < V; i++)
        glVertex2f(P_new[0][i], P_new[1][i]);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    V = 4;
    //    cout<<"Enter the number of vertices in polygon : ";
    //    cin>>V;

    P_old[0][0] = 100;
    P_old[1][0] = 100;
    P_old[2][0] = 1;
    P_old[0][1] = 100;
    P_old[1][1] = 200;
    P_old[2][1] = 1;
    P_old[0][2] = 200;
    P_old[1][2] = 200;
    P_old[2][2] = 1;
    P_old[0][3] = 200;
    P_old[1][3] = 100;
    P_old[2][3] = 1;
    //    cout<<"Enter the coordinates of the vertices:\n";
    //    for(int i=0; i<V; i++) {
    //        cin>>P_old[0][i];   // x coordinate
    //        cin>>P_old[1][i];   // y cooridnate
    //        P_old[2][i] = 1;
    //    }

    cout << "2D Transformations:\n";
    cout << "1. Translation\n";
    cout << "2. Scaling\n";
    cout << "3. Rotation\n";
    cout << "4. Reflection\n";
    cout << "5. Shearing\n";
    cout << "Enter transformation choice: ";
    cin >> C;

    float tx, ty, sx, sy, theta, X, Y, sh;
    char axis;

    switch (C)
    {
    case 1:
        tx = 50;
        ty = 70;
        //                cout<<"Enter Translation/Shift vector: ";
        //                cin>>tx>>ty;

        T[0][0] = 1;
        T[0][1] = 0;
        T[0][2] = tx;
        T[1][0] = 0;
        T[1][1] = 1;
        T[1][2] = ty;
        T[2][0] = 0;
        T[2][1] = 0;
        T[2][2] = 1;
        break;

    case 2:
        sx = 1.5;
        sy = 1.5;
        //                cout<<"Enter Scaling factor: ";
        //                cin>>sx>>sy;

        T[0][0] = sx;
        T[0][1] = 0;
        T[0][2] = 0;
        T[1][0] = 0;
        T[1][1] = sy;
        T[1][2] = 0;
        T[2][0] = 0;
        T[2][1] = 0;
        T[2][2] = 1;
        break;

    case 3:
        theta = 30;
        //                cout<<"Enter rotation angle: ";
        //                cin>>theta;
        theta = theta * (3.14159265359 / 180.0);

        T[0][0] = cos(theta);
        T[0][1] = -sin(theta);
        T[0][2] = 0;
        T[1][0] = sin(theta);
        T[1][1] = cos(theta);
        T[1][2] = 0;
        T[2][0] = 0;
        T[2][1] = 0;
        T[2][2] = 1;
        break;

    case 4:
        X = 0;
        Y = 0;
        axis = 'X';
        //                cout<<"Enter the axis along which reflection to take: ";
        //                cin>>axis;
        if (axis == 'X' || axis == 'x')
            Y = 1;
        else
            X = 1;

        T[0][0] = pow(-1, X);
        T[0][1] = 0;
        T[0][2] = 0;
        T[1][0] = 0;
        T[1][1] = pow(-1, Y);
        T[1][2] = 0;
        T[2][0] = 0;
        T[2][1] = 0;
        T[2][2] = 1;
        break;

    case 5:
        sh = 1.5;
        X = 0;
        Y = 0;
        axis = 'X';
        //                cout<<"Enter the axis along which shearing to take: ";
        //                cin>>axis;
        //                cout<<"Enter Shearing parameter: ";
        //                cin>>sh;
        if (axis == 'X' || axis == 'x')
            X = 1;
        else
            Y = 1;

        T[0][0] = 1;
        T[0][1] = sh * X;
        T[0][2] = 0;
        T[1][0] = sh * Y;
        T[1][1] = 1;
        T[1][2] = 0;
        T[2][0] = 0;
        T[2][1] = 0;
        T[2][2] = 1;
        break;

    default:
        cout << "Wrong Transformation choice\n";
        return -1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 800);
    glutCreateWindow("2D Transformations");
    gluOrtho2D(-200, 600, -400, 400);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
    return 0;
}