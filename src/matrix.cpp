#include "matrix.hpp"

Matrix::Matrix(int width, int height)
{
	this->width = width;
	this->height = height;
	this->len = width * height;

	this->grid = new Element[len];
}

void Matrix::step()
{
	//Process the queue
	while(!actionQueue.empty())
	{
		auto func = actionQueue.front();
		
		func();
		
		actionQueue.pop();
	}
	
	for(int i = 0; i < len; i++)
	{
		grid[i].step(this, i % width, i / width);
	}
}

void Matrix::draw(sf::Uint8 *pixels)
{
	for(int i = 0; i < len; i++)
	{
		pixels[i * 4] = grid[i].color[0];//grid[i].value;
		pixels[i * 4 + 1] = grid[i].color[1];//grid[i].value;
		pixels[i * 4 + 2] = grid[i].color[2];//grid[i].value;
		pixels[i * 4 + 3] = grid[i].color[3];//255;
	}
}

int Matrix::getIndex(int x, int y)
{
	int index = y * width + x;
	
	if(index >= len) throw std::invalid_argument("Index out of bounds");
	
	return index;
}

Element &Matrix::operator()(int x, int y)
{
	return grid[getIndex(x, y)];
}

void Matrix::setElementAt(int x, int y, Element::Type type)
{
	auto &elem = grid[getIndex(x, y)];
	
	if(elem.type == type) return;
	
	elem.type = type;
	elem.setColor();
}

void Matrix::swapPlace(int x1, int y1, int x2, int y2)
{
	Element &elem1 = (*this)(x1, y1);
	Element &elem2 = (*this)(x2, y2);
	
	Element::Type temp = elem1.type;
	elem1.type = elem2.type;
	elem2.type = temp;
	
	elem1.setColor();
	elem2.setColor();
}