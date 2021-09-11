#pragma once

#include "Shape.h"
#include "MenuDrawing.h"

class property_group
{
public:
	const char* name;
	shape* data;

	property_group(const char* _name, shape* _data) :
		name(_name),
		data(_data)
	{
	}
	
	virtual void draw() const = 0;
};

class circle_property_group : public property_group
{
public:
	circle_property_group(circle* _data) :
		property_group("Circle", _data)
	{
	}
	
	void draw() const override
	{
		draw_properties(*static_cast<circle*>(data));
	}
};

class square_property_group : public property_group
{
public:
	square_property_group(square* _data) :
		property_group("Square", _data)
	{	
	}
	
	void draw() const override
	{
		draw_properties(*static_cast<square*>(data));
	}
};

class rectangle_property_group : public property_group
{
public:
	rectangle_property_group(rectangle* _data) :
		property_group("Rectangle", _data)
	{	
	}
	
	void draw() const override
	{
		draw_properties(*static_cast<rectangle*>(data));
	}
};