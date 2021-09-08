#pragma once

#include "cinder/Color.h"

enum shape_type { BASE, CIRCLE, SQUARE, RECTANGLE };

class shape
{
public:
	cinder::vec2 location;
	cinder::Color color;
	shape_type type;

	shape()
		: type(BASE)
	{
	}
	
	explicit shape(const shape_type shape_type)
		: type(shape_type)
	{
	}
};

class circle : public shape
{
public:
	float radius;

	circle() :
		shape(CIRCLE),
		radius(0.0f)
	{
	}
	
	bool is_inside(const cinder::vec2& pos) const
	{
		const cinder::vec2 v = pos - location;
		return v.x * v.x + v.y * v.y <= radius * radius;
	}
};

class moving_circle : public circle
{
public:
	cinder::vec2 direction;
	float velocity;

	moving_circle() :
		direction{0.0f, 0.0f},
		velocity(0.0f)
	{
	}
};

class square : public shape
{
public:
	float side;

	explicit square() :
		shape(SQUARE),
		side(0.0f)
	{
	}
};

class rectangle : public shape
{
public:
	ci::vec2 size;

	rectangle() :
		shape(RECTANGLE),
		size{0.0f, 0.0f}
	{
	}
};
