#pragma once

#include "cinder/Color.h"
#include "cinder/Vector.h"

enum ShapeType { CIRCLE, SQUARE, RECTANGLE };

class Shape
{
public:
	cinder::vec2 location;
	cinder::Color color;
	ShapeType type;
};

class Circle : public Shape
{
public:
	float radius;

	inline bool isInside(const cinder::vec2& pos)
	{
		const cinder::vec2 v = pos - location;
		return v.x * v.x + v.y * v.y <= radius * radius;
	}
};

class MovingCircle : public Circle
{
public:
	cinder::vec2 direction;
	float velocity;
};

class Square : public Shape
{
public:
	float side;
};

class Rectangle : public Shape
{
public:
	float width;
	float height;
};
