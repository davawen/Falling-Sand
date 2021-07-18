#include "element.hpp"
#include "matrix.hpp"

Element::Element(Element::Type type)
{
	this->type = type;

	this->setColor();
}

void Element::step(Matrix *matrix, int x, int y)
{
	switch(type)
	{
		case Element::Type::Sand:
			// Go down
			if(y >= matrix->height-2) break;

			if((*matrix)(x, y+1).isFluid())
			{
				matrix->actionQueue.push(
					[=]()
					{
						matrix->swapPlace(x, y, x, y+1);
					}
				);
			}
			else
			{
				int dir = (rand() % 2 == 0 ? ( x <= 1 ? 1 : -1 ) : ( x >= matrix->width-2 ? -1 : 1 ));
				
				if((*matrix)(x + dir, y).isFluid() && (*matrix)(x + dir, y + 1).isFluid())
				{
					matrix->actionQueue.push(
						[=]()
						{
							matrix->swapPlace(x, y, x + dir, y + 1);
						}
					);
				}
			}
			break;
		case Element::Type::Water:
			if((*matrix)(x, y + 1).isEmpty())
			{
				if(y >= matrix->height - 2) break;
				
				matrix->actionQueue.push(
					[=]()
					{
						matrix->swapPlace(x, y, x, y + 1);
					}
				);
			}
			else
			{
				int dir = (rand() % 2 == 0 ? (x <= 1 ? 1 : -1) : (x >= matrix->width - 2 ? -1 : 1));
				
				bool neighbourEmpty = (*matrix)(x + dir, y).isEmpty();
				
				if(neighbourEmpty && (*matrix)(x + dir, y + 1).isEmpty())
				{
					matrix->actionQueue.push(
						[=]()
						{
							matrix->swapPlace(x, y, x + dir, y + 1);
						}
					);
				}
				else if(neighbourEmpty)
				{
					matrix->actionQueue.push(
						[=]()
						{
							matrix->swapPlace(x, y, x + dir, y);
						}
					);
				}
			}
			break;
		default:
			break;
	}
}

void Element::setColor()
{
	switch(type)
	{
		case Element::Type::Empty:
			color[3] = 0; // Set opacity to 0
			break;
		case Element::Type::Sand:
			color[0] = 247;
			color[1] = 230;
			color[2] = 57;
			color[3] = 255;
			break;
		case Element::Type::Water:
			color[0] = 60;
			color[1] = 130;
			color[2] = 255;
			color[3] = 255;
			break;
		case Element::Type::Stone:
			color[0] = 175;
			color[1] = 175;
			color[2] = 162;
			color[3] = 255;
			break;
	}
}

bool Element::isEmpty()
{
	return type == Element::Type::Empty;
}

bool Element::isFluid()
{
	return type == Element::Type::Empty || type == Element::Type::Water;
}