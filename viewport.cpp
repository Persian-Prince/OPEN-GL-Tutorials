#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

void WindowtoViewport(int x_w, int y_w, int x_wmax, int y_wmax, int x_wmin, int y_wmin, int x_vmax, int y_vmax, int x_vmin, int y_vmin)
{
	int x_v, y_v;
    float sx, sy;

	sx = (float)(x_vmax - x_vmin) / (x_wmax - x_wmin);
	sy = (float)(y_vmax - y_vmin) / (y_wmax - y_wmin);

	x_v = x_vmin + (float)((x_w - x_wmin) * sx);
	y_v = y_vmin + (float)((y_w - y_wmin) * sy);

	cout<< "The point on viewport: ("<<x_v <<","<< y_v<<")" ;
}

int main(int argc, char** argv)
{
	int x_wmax = 80, y_wmax = 80, x_wmin = 20, y_wmin = 40;
	int x_vmax = 60, y_vmax = 60, x_vmin = 30, y_vmin = 40;
	int x_w = 30, y_w = 80;

	WindowtoViewport(30, 80, 80, 80, 20, 40, 60, 60, 30, 40);
    
    return 0;
}
