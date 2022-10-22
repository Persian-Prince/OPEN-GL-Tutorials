#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

FILE *fp;
class Edge
{
public:
    int ymax;
    float xofymin;
    float slopeinverse;
};

class EdgeTableRow
{
public:
    int count;
    Edge edges[(int)1e5];
    EdgeTableRow()
    {
        count = 0;
    }
    void print()
    {
        for (int j = 0; j < count; j++)
        {
            cout << fixed << setprecision(2);
            cout << "\tymax = " << edges[j].ymax << " x at ymin =" << edges[j].xofymin << " 1/m = " << edges[j].slopeinverse << endl;
        }
    }
} EdgeTable[800], ActiveEdgeTuple;

void printEdgeTable()
{
    for (int i = 0; i < 800; i++)
    {
        if (EdgeTable[i].count > 0)
            cout << "Scanline #" << i << endl;
        EdgeTable[i].print();
    }
}
void sortEdgeTableRow(EdgeTableRow *ett)
{
    for (int i = 1; i < ett->count; i++)
    {
        Edge temp;
        temp.ymax = ett->edges[i].ymax;
        temp.xofymin = ett->edges[i].xofymin;
        temp.slopeinverse = ett->edges[i].slopeinverse;
        int j = i - 1;
        while ((temp.xofymin < ett->edges[j].xofymin) && (j >= 0))
        {
            ett->edges[j + 1].ymax = ett->edges[j].ymax;
            ett->edges[j + 1].xofymin = ett->edges[j].xofymin;
            ett->edges[j + 1].slopeinverse =
                ett->edges[j].slopeinverse;
            j = j - 1;
        }
        ett->edges[j + 1].ymax = temp.ymax;
        ett->edges[j + 1].xofymin = temp.xofymin;
        ett->edges[j + 1].slopeinverse = temp.slopeinverse;
    }
}
void storeEdgeInTuple(EdgeTableRow *row, int ym, int xm, float slopInv)
{
    row->edges[row->count].ymax = ym;
    row->edges[row->count].xofymin = xm;
    row->edges[row->count].slopeinverse = slopInv;
    row->count++;
    sortEdgeTableRow(row);
}
void storeEdgeInTable(int x1, int y1, int x2, int y2)
{
    float m, inverseSlope;
    int Ymax, XatminY, Yscanline;
    if (y2 == y1)
        return;
    inverseSlope = (x2 - x1 - 0.0) / (y2 - y1);
    cout << "Inverse Slope for (" << x1 << ", " << y1 << ") -> (" << x2 << ", " << y2 << ") = " << inverseSlope << endl;
    if (y1 > y2)
    {
        Yscanline = y2;
        Ymax = y1;
        XatminY = x2;
    }
    else
    {
        Yscanline = y1;
        Ymax = y2;
        XatminY = x1;
    }
    storeEdgeInTuple(&EdgeTable[Yscanline], Ymax, XatminY, inverseSlope);
}

void removeEdgeByYmax(EdgeTableRow *Tup, int Ymax)
{
    for (int i = 0; i < Tup->count; i++)
    {
        if (Tup->edges[i].ymax == Ymax)
        {
            cout << "Removed edge at " << Ymax << endl;
            for (int j = i; j < Tup->count - 1; j++)
            {
                Tup->edges[j].ymax = Tup->edges[j + 1].ymax;
                Tup->edges[j].xofymin = Tup->edges[j + 1].xofymin;
                Tup->edges[j].slopeinverse = Tup->edges[j + 1].slopeinverse;
            }
            Tup->count--;
            i--;
        }
    }
}
void UpdateXusingInverseSlope(EdgeTableRow *Tup)
{
    for (int i = 0; i < Tup->count; i++)
    {
        Tup->edges[i].xofymin = Tup->edges[i].xofymin +
                                Tup->edges[i].slopeinverse;
    }
}
void ScanlineFillAlgorithm()
{
    int x1, ymax1, x2, ymax2, flag = 0, coordCount;
    for (int i = 0; i < 800; i++)
    {
        for (int j = 0; j < EdgeTable[i].count; j++)
        {
            storeEdgeInTuple(&ActiveEdgeTuple,
                             EdgeTable[i].edges[j].ymax,
                             EdgeTable[i].edges[j].xofymin,
                             EdgeTable[i].edges[j].slopeinverse);
        }
        ActiveEdgeTuple.print();
        removeEdgeByYmax(&ActiveEdgeTuple, i);
        sortEdgeTableRow(&ActiveEdgeTuple);
        ActiveEdgeTuple.print();
        int j = 0;
        flag = 0;
        coordCount = 0;
        x1 = 0;
        x2 = 0;
        ymax1 = 0;
        ymax2 = 0;
        while (j < ActiveEdgeTuple.count)
        {
            if (coordCount % 2 == 0)
            {
                x1 = ActiveEdgeTuple.edges[j].xofymin;
                ymax1 = ActiveEdgeTuple.edges[j].ymax;
                if ((x1 == x2) && (((x1 == ymax1) && (x2 != ymax2)) || ((x1 != ymax1) && (x2 == ymax2))))
                {
                    x2 = x1;
                    ymax2 = ymax1;
                }
                else
                    coordCount++;
            }
            else
            {
                x2 = ActiveEdgeTuple.edges[j].xofymin;
                ymax2 = ActiveEdgeTuple.edges[j].ymax;
                flag = 0;
                if ((x1 == x2) && (((x1 == ymax1) && (x2 != ymax2)) || ((x1 != ymax1) && (x2 == ymax2))))
                {
                    x1 = x2;
                    ymax1 = ymax2;
                }
                else
                {
                    coordCount++;
                    flag = 1;
                }
                if (flag)
                {
                    glColor3f(0.6, 0.1, 0.4);
                    glBegin(GL_LINES);
                    glVertex2i(x1, i);
                    glVertex2i(x2, i);
                    glEnd();
                    glFlush();
                }
            }
            j++;
        }
        UpdateXusingInverseSlope(&ActiveEdgeTuple);
    }
    cout << "Scanline filling complete" << endl;
}
void DrawFigure()
{
    glColor3f(0, 0, 1);
    int count = 0, x1, y1, x2, y2;
    rewind(fp);
    while (!feof(fp))
    {
        count++;
        if (count > 2)
        {
            x1 = x2;
            y1 = y2;
            count = 2;
        }
        if (count == 1)
        {
            fscanf(fp, "%d,%d", &x1, &y1);
        }
        else
        {
            fscanf(fp, "%d,%d", &x2, &y2);
            cout << "Scanned Point = " << x2 << ", " << y2 << endl;
            glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
            glEnd();
            storeEdgeInTable(x1, y1, x2, y2);
            glFlush();
        }
    }
}
void DrawAndFillFigure(void)
{
    DrawFigure();
    cout << "Table" << endl;
    printEdgeTable();
    ScanlineFillAlgorithm();
}
void vgl_init(int &argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Scan Line Filling Algorithm");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-320, 320, -240, 240);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(DrawAndFillFigure);
    glutMainLoop();
}

int main(int argc, char** argv)
{
    fp = fopen("vertex1.txt", "r");
    if (fp == NULL)
    {
        printf("Could not open file");
        return 0;
    }
    vgl_init(argc, argv);
    fclose(fp);
    return 0;
}
