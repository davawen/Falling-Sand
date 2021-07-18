#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <functional>
#include <SFML/Graphics.hpp>

struct Element;

#include "element.hpp"

struct Matrix
{
	std::queue<std::function<void()>> actionQueue;
	
	Element *grid;

	int width;
	int height;
	int len;

	Matrix(int width, int height);

	void step();

	/// @param pixels Array containing pixel data
	void draw(sf::Uint8 *pixels);
	
	int getIndex(int x, int y);
	
	Element &operator()(int x, int y);
	
	void setElementAt(int x, int y, Element::Type type);
	void swapPlace(int x1, int y1, int x2, int y2);
};

#endif