# pragma once

#include "document.h"
#include "Shape.h"

using namespace rapidjson;

template<class T>
void deserialize(T& target, Value& value)
{
}

template<>
inline void deserialize<ci::vec2>(ci::vec2& target, Value& value)
{
	if (value.HasMember("x") && value["x"].IsNumber())
		target.x = value["x"].GetFloat();
	if (value.HasMember("y") && value["y"].IsNumber())
		target.y = value["y"].GetFloat();
}

template<>
inline void deserialize<ci::Color>(ci::Color& target, Value& value)
{
	unsigned long val;
	try
	{
		val = std::stoul(value.GetString(), nullptr, 16);
	}
	catch (std::invalid_argument&)
	{
		return;
	}
	catch(std::out_of_range&)
	{
		return;
	}
	
	target = ci::Color::hex(val);
}

template<>
inline void deserialize<shape>(shape& target, Value& value)
{
	if (value.HasMember("location") && value["location"].IsObject())
		deserialize<ci::vec2>(target.location, value["location"]);
	if (value.HasMember("color") && value["color"].IsString())
		deserialize<ci::Color>(target.color, value["color"]);
	if (value.HasMember("type") && value["type"].IsInt())
		NULL;  // TODO
}

template<>
inline void deserialize<circle>(circle& target, Value& value)
{
	deserialize<shape>(target, value);
	if (value.HasMember("radius") && value["radius"].IsNumber())
		target.radius = value["radius"].GetFloat();
}

template<>
inline void deserialize<square>(square& target, Value& value)
{
	deserialize<shape>(target, value);
	if (value.HasMember("side") && value["side"].IsNumber())
		target.side = value["side"].GetFloat();
}

template<>
inline void deserialize<rectangle>(rectangle& target, Value& value)
{
	deserialize<shape>(target, value);
	if (value.HasMember("size") && value.IsObject())
		deserialize<ci::vec2>(target.size, value["size"]);
}

template<class T>
void deserialize_object(T& target, Value& value, const char* name)
{
	if (value.HasMember(name) && value[name].IsObject())
		deserialize<T>(target, value[name]);
}