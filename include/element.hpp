#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include <SFML/Graphics.hpp>

struct Matrix;

struct Element
{
	enum struct Type
	{
		Empty,
		Sand,
		Water,
		Stone
	};
	
	Element::Type type;

	sf::Uint8 color[4];
	
	Element(Element::Type type = Element::Type::Empty);

	/// @param x Describe the x position of itself
	/// @param y Describe the y position of itself
	void step(Matrix *matrix, int x, int y);
	
	/// Sets the color of the element based on its current type
	void setColor();
	
	
	// Utility functions
	
	inline bool isEmpty();
	inline bool isFluid();
	inline bool isSolid();
};

#endif