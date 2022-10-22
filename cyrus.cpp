#include <GL/glut.h>
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void drawline(RenderWindow* window, pair<int, int> p0, pair<int, int> p1)
{
	Vertex line[] = {
		Vertex(Vector2f(p0.first, p0.second)),
		Vertex(Vector2f(p1.first, p1.second))
	};
	window->draw(line, 2, Lines);
}

void drawPolygon(RenderWindow* window, pair<int, int> vertices[], int n)
{
	for (int i = 0; i < n - 1; i++)
		drawline(window, vertices[i], vertices[i + 1]);
	drawline(window, vertices[0], vertices[n - 1]);
}

int dot(pair<int, int> p0, pair<int, int> p1)
{
	return p0.first * p1.first + p0.second * p1.second;
}

float max(vector<float> t)
{
	float maximum = INT_MIN;
	for (int i = 0; i < t.size(); i++)
		if (t[i] > maximum)
			maximum = t[i];
	return maximum;
}

float min(vector<float> t)
{
	float minimum = INT_MAX;
	for (int i = 0; i < t.size(); i++)
		if (t[i] < minimum)
			minimum = t[i];
	return minimum;
}

pair<int, int>* CyrusBeck(pair<int, int> vertices[], pair<int, int> line[], int n)
{
	pair<int, int>* newPair = new pair<int, int>[2];
	pair<int, int>* normal = new pair<int, int>[n];
	for (int i = 0; i < n; i++) {
		normal[i].second = vertices[(i + 1) % n].first - vertices[i].first;
		normal[i].first = vertices[i].second - vertices[(i + 1) % n].second;
	}
	pair<int, int> P1_P0 = make_pair(line[1].first - line[0].first, line[1].second - line[0].second);
	pair<int, int>* P0_PEi = new pair<int, int>[n];
	for (int i = 0; i < n; i++) {
		P0_PEi[i].first = vertices[i].first - line[0].first;
		P0_PEi[i].second = vertices[i].second - line[0].second;
	}
	int *numerator = new int[n], *denominator = new int[n];
	for (int i = 0; i < n; i++) {
		numerator[i] = dot(normal[i], P0_PEi[i]);
		denominator[i] = dot(normal[i], P1_P0);
	}
	float* t = new float[n];
	vector<float> tE, tL;

	for (int i = 0; i < n; i++) {
		t[i] = (float)(numerator[i]) / (float)(denominator[i]);
		if (denominator[i] > 0)
			tE.push_back(t[i]);
		else
			tL.push_back(t[i]);
	}
	float temp[2];
	tE.push_back(0.f);
	temp[0] = max(tE);
	tL.push_back(1.f);
	temp[1] = min(tL);

	if (temp[0] > temp[1]) {
		newPair[0] = make_pair(-1, -1);
		newPair[1] = make_pair(-1, -1);
		return newPair;
	}

	newPair[0].first = (float)line[0].first + (float)P1_P0.first * (float)temp[0];
	newPair[0].second = (float)line[0].second + (float)P1_P0.second * (float)temp[0];
	newPair[1].first = (float)line[0].first + (float)P1_P0.first * (float)temp[1];
	newPair[1].second = (float)line[0].second+ (float)P1_P0.second * (float)temp[1];
	cout << '(' << newPair[0].first << ", "<< newPair[0].second << ") ("<< newPair[1].first << ", "<< newPair[1].second << ")";
	return newPair;
}

int main(int argc, char** argv)
{
	RenderWindow window(VideoMode(500, 500), "Cyrus Beck");
	pair<int, int> vertices[]
		= { make_pair(200, 50),
			make_pair(250, 100),
			make_pair(200, 150),
			make_pair(100, 150),
			make_pair(50, 100),
			make_pair(100, 50) };
	int n = sizeof(vertices) / sizeof(vertices[0]);
	pair<int, int> line[] = { make_pair(10, 10), make_pair(450, 200) };
	pair<int, int>* temp1 = CyrusBeck(vertices, line, n);
	pair<int, int> temp2[2];
	temp2[0] = line[0];
	temp2[1] = line[1];
	bool trigger = false;
	while (window.isOpen()) {
		window.clear();
		Event event;
		if (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				trigger = !trigger;
		}
		drawPolygon(&window, vertices, n);
		if (trigger) {
			line[0] = temp1[0];
			line[1] = temp1[1];
		}
		else {
			line[0] = temp2[0];
			line[1] = temp2[1];
		}
		drawline(&window, line[0], line[1]);
		window.display();
	}
    return 0;
}
