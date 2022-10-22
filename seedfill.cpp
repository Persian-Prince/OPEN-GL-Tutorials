#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

int V = 0;
float X[100], Y[100], Xc = 0, Yc = 0;

struct Color
{
    float r;
    float g;
    float b;
};

Color getPixelColor(int x, int y)
{
    Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

void setPixelColor(GLint x, GLint y, Color color)
{
    glBegin(GL_POINTS);
    glColor3f(color.r, color.g, color.b);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void floodFill(GLint x, GLint y, Color oldColor, Color newColor)
{
    Color color;
    color = getPixelColor(x, y);

    if (color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b)
    {
        setPixelColor(x, y, newColor);
        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
    }
    return;
}

void onMouseClick(int button, int state, int x, int y)
{
    Color newColor = {1.0f, 0.0f, 0.0f};
    Color oldColor = {1.0f, 1.0f, 1.0f};

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        floodFill(Xc, Yc, oldColor, newColor);
}

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < V; i++)
        glVertex2f(X[i], Y[i]);
    glEnd();

    Color newColor = {1.0f, 0.0f, 0.0f};
    Color oldColor = {0.0f, 0.0f, 0.0f};
    floodFill(Xc, Yc, oldColor, newColor);

    glFlush();
}

int main(int argc, char** argv)
{
    cout << "Enter the number of vertices in polygon : ";
    cin >> V;
    cout << "Enter the coordinates of the vertices: ";
    for (int i = 0; i < V; i++)
    {
        cin >> X[i] >> Y[i];

        Xc += X[i];
        Yc += Y[i];
    }

    Xc = Xc / V;
    Yc = Yc / V;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Polygon Filling using Seed Fill Algorithm");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMouseFunc(onMouseClick);
    glutMainLoop();
    return 0;
}